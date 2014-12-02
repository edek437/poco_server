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
	static Poco::RWLock db_rwlock;
	static Poco::RWLock mes_rwlock;
	static std::vector<std::string> messages;
	static std::map<std::string, Poco::Net::SocketAddress> database;
public:
	MyTCPServerConnection(const Poco::Net::StreamSocket & sock);
	void run();
	~MyTCPServerConnection();
};

#endif /* MYTCPSERVERCONNECTION_H_ */
