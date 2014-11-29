/*
 * server_framework.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: ztp
 */

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"
#include "Poco/RWLock.h"
#include <iostream>
#include <map>
#include <string.h>
#include <sstream>
#include "Who.h"
#include "Nick.h"
#include "Get_command.h"

//TODO: figure out what going on and comment it
Handler *handler_factory(std::string str, Poco::Net::StreamSocket & sock) {
	std::string command=get_command(str);
	if (command == "who") {
		return new Who(sock);
	} else if (command == "nick") {
		std::cout<<"Passing to nick changer: "<<str<<std::endl;
		return new Nick(sock,str);
	} else
		return NULL;
}

class MyTCPServerConnection: public Poco::Net::TCPServerConnection {
private:
	static Poco::RWLock db_rwlock;
	static Poco::Mutex sr_mutex; //send/receive lock
	static std::map<std::string, Poco::Net::SocketAddress> database;
public:
	MyTCPServerConnection(const Poco::Net::StreamSocket & sock) :
			Poco::Net::TCPServerConnection(sock) {
		db_rwlock.writeLock();
		database[sock.peerAddress().toString()] = sock.peerAddress();
		db_rwlock.unlock();
	}

	void run() {
		std::cout << "running" << std::endl;
		for (;;) { //it will exit when I close socket from client side
			char buffer[1024];
			int rec = socket().receiveBytes((char *) buffer,
					sizeof(buffer) - 1); //-1 to prevent putting '\0' out of buffer range
			buffer[rec] = '\0';
			std::cout << "Received: " << buffer << std::endl;
			Handler *h = handler_factory(buffer, socket());
			if (h)
//TODO: add mutex as handle parameter
				h->handle(database, db_rwlock);
			else { //when it's done only way to get inside else is by sending quit request from client
				std::cout << "Sorry not implemented yet" << std::endl;
				break;
			}
		}
//TODO: put receive to function and do some mutex stuff with it
	}

	~MyTCPServerConnection() {
		std::cout << "deleting from connected users database"<<std::endl;
		std::cout << "ending connection" << std::endl;
	}
};

Poco::RWLock MyTCPServerConnection::db_rwlock;
Poco::Mutex MyTCPServerConnection::sr_mutex;
std::map<std::string, Poco::Net::SocketAddress> MyTCPServerConnection::database;

class MyTCPServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory {

public:
	Poco::Net::TCPServerConnection* createConnection(
			const Poco::Net::StreamSocket & sock) {
		std::cout << "create connection\n";
//shared ptr take care of this dynamic allocation
		return new MyTCPServerConnection(sock);
	}
};

int main(int argc, char** argv) {
	Poco::Net::TCPServerConnectionFactory::Ptr pTSCF =
			new MyTCPServerConnectionFactory(); //Ptr is hared pointer here
	Poco::Net::ServerSocket ser_sock(8080); //bind+listen
	Poco::Net::TCPServer server(pTSCF, ser_sock);
	server.start();
	while (1) {
	}
	server.stop();
	return 0;
}
