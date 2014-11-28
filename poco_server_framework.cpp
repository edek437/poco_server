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
#include "Poco/Util/ServerApplication.h"
#include <iostream>
#include <map>
#include <string.h>

class MyTCPServerConnection;

//TODO: figure out what going on and comment it
class Handler {
public:
	virtual void handle()=0;
	virtual ~Handler() {
	}
	;
};

class Who: public Handler {
	Poco::Net::StreamSocket socket;
public:
	Who(Poco::Net::StreamSocket & sock) :
			socket(sock) {
	}
	void handle() {
		char answer[] = "received who request";
		socket.sendBytes((char *) answer, strlen(answer));
	}
};

Handler *handler_factory(std::string str, Poco::Net::StreamSocket & sock) {
	if (str == "who")
		return new Who(sock);
	else
		return NULL;
}

class MyTCPServerConnection: public Poco::Net::TCPServerConnection {
private:
	static Poco::Mutex db_mutex;
	static std::map<std::string, Poco::Net::SocketAddress> database;
public:
	MyTCPServerConnection(const Poco::Net::StreamSocket & sock) :
			Poco::Net::TCPServerConnection(sock) {
		db_mutex.lock();
		database[sock.peerAddress().toString()] = sock.peerAddress();
		db_mutex.unlock();
	}

//TODO: what is run doing
	void run() {
		std::cout << "running" << std::endl;
		for (;;) { //it will exit when I close socket from client side
			char buffer[1024];
			int rec = socket().receiveBytes((char *) buffer,
					sizeof(buffer) - 1); //-1 to prevent putting '\0' out of buffer range
			buffer[rec] = '\0';
			std::cout << "Received: " << buffer << std::endl;
			Handler *h = handler_factory(buffer, socket()); //ten socket jest zly
			if (h)
				h->handle();
			else
				std::cout << "Sorry not implemented yet" << std::endl;
		}
//TODO: put receive to function and do some mutex stuff with it
	}

	~MyTCPServerConnection() {
		std::cout << "ending connection" << std::endl;
	}
};

Poco::Mutex MyTCPServerConnection::db_mutex;
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
