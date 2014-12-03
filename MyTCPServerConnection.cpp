/*
 * MyTCPServerConnection.cpp
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#include "MyTCPServerConnection.h"
#include "Poco/SharedPtr.h"
#include <iostream>

MyTCPServerConnection::MyTCPServerConnection(const Poco::Net::StreamSocket & sock,
		Poco::RWLock *db_rwl, Poco::RWLock *mes_rwl,
		std::vector<MessageStruct> *mes,
		std::map<std::string, Poco::Net::SocketAddress> *db) :
			Poco::Net::TCPServerConnection(sock), db_rwlock(db_rwl), mes_rwlock(mes_rwl), messages(mes), database(db) {
		db_rwlock->writeLock();
		database->insert(std::pair<std::string, Poco::Net::SocketAddress> (sock.peerAddress().toString(),sock.peerAddress()));
		db_rwlock->unlock();
	}


void MyTCPServerConnection::run() {
	std::cout << "running" << std::endl;
	for (;;) { //it will exit when I close socket from client side
		char buffer[1024];
		int rec = socket().receiveBytes((char *) buffer, sizeof(buffer) - 1); //-1 to prevent putting '\0' out of buffer range
		buffer[rec] = '\0';
		//std::cout << "Received: " << buffer << std::endl;
		Handler *h = handler_factory(buffer, socket(), db_rwlock, mes_rwlock,
				database, messages);
		Poco::SharedPtr<Handler> phandler(h);
		if (h)
			h->handle();
		else { //when it's done only way to get inside else is by sending quit request from client
			std::cout << "Ending connection" << std::endl;
			break;
		}
	}
}

MyTCPServerConnection::~MyTCPServerConnection() {
	std::cout << "deleting from connected users database" << std::endl;
	db_rwlock->writeLock();
	for (std::map<std::string, Poco::Net::SocketAddress>::iterator mit =
			database->begin(); mit != database->end();) {
		if (mit->second.toString() == socket().peerAddress().toString()) {
			database->erase(mit);
			break;
		}
		mit++;
	}
	db_rwlock->unlock();
	std::cout << "ending connection" << std::endl;
}
