/*
 * MyTCPServerConnectionFactory.h
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#ifndef MYTCPSERVERCONNECTIONFACTORY_H_
#define MYTCPSERVERCONNECTIONFACTORY_H_

#include "MyTCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

class MyTCPServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory {
public:
	Poco::Net::TCPServerConnection* createConnection(
			const Poco::Net::StreamSocket & sock);
};

#endif /* MYTCPSERVERCONNECTIONFACTORY_H_ */
