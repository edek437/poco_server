/*
 * MyTCPServerConnection.h
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#ifndef MYTCPSERVERCONNECTION_H_
#define MYTCPSERVERCONNECTION_H_

#include "handler_factory.h"
#include "Poco/Net/TCPServerConnection.h"

class MyTCPServerConnection: public Poco::Net::TCPServerConnection {
private:
	Poco::RWLock *db_rwlock;
	Poco::RWLock *mes_rwlock;
	std::vector<std::string> *messages;
	std::map<std::string, Poco::Net::SocketAddress> *database;
public:
	MyTCPServerConnection(const Poco::Net::StreamSocket & sock,
			Poco::RWLock *db_rwl, Poco::RWLock *mes_rwl,
			std::vector<std::string> *mes,
			std::map<std::string, Poco::Net::SocketAddress> *db);
	void run();
	~MyTCPServerConnection();
};

#endif /* MYTCPSERVERCONNECTION_H_ */
