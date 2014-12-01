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
#include <vector>
#include <string.h>
#include <sstream>
#include "Who.h"
#include "Nick.h"
#include "Message.h"
#include "New.h"
#include "MessageDbUp.h"
#include "Get_command.h"

Handler *handler_factory(std::string str, Poco::Net::StreamSocket & sock,
		Poco::RWLock *db_rwl, Poco::RWLock *mes_rwl,
		std::map<std::string, Poco::Net::SocketAddress> *database,
		std::vector<std::string> *messages) {
	std::string command = get_command(str);
	if (command == "who") {
		return new Who(sock,database, db_rwl);
	} else if (command == "nick") {
		return new Nick(sock, str,database,db_rwl);
	} else if (command == "msg") {
		std::cout << "Looking for: " << str << std::endl;
		return new Message(sock, str,database,db_rwl);
	} else if (command == "msg2") {
		return new MessageDbUp(sock, str,messages,mes_rwl);
	} else if (command == "new") {
		return new New(sock,str,messages, mes_rwl);
	} else
		return NULL;
}

class MyTCPServerConnection: public Poco::Net::TCPServerConnection {
private:
	static Poco::RWLock db_rwlock;
	static Poco::RWLock mes_rwlock;
	static std::vector<std::string> messages;
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
//TODO: make it possible to pass buffer by reference
			Handler *h = handler_factory(buffer, socket(), &db_rwlock,
					&mes_rwlock, &database, &messages);
			Poco::SharedPtr<Handler> phandler(h);
			if (h)
				h->handle();
			else { //when it's done only way to get inside else is by sending quit request from client
				std::cout << "Ending connection" << std::endl;
				break;
			}
		}
	}

	~MyTCPServerConnection() {
		std::cout << "deleting from connected users database" << std::endl;
		for (std::map<std::string, Poco::Net::SocketAddress>::iterator mit =
				database.begin(); mit != database.end(); mit++) {
			if (mit->second.toString() == socket().peerAddress().toString()) {
				database.erase(mit);
			}
		}
		std::cout << "ending connection" << std::endl;
	}
};

Poco::RWLock MyTCPServerConnection::db_rwlock;
Poco::RWLock MyTCPServerConnection::mes_rwlock;
std::vector<std::string> MyTCPServerConnection::messages;
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
