/*
 * MyTCPServerConnectionFactory.cpp
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#include "MyTCPServerConnectionFactory.h"
#include <iostream>

Poco::Net::TCPServerConnection* MyTCPServerConnectionFactory::createConnection(
		const Poco::Net::StreamSocket & sock) {
	std::cout << "create connection\n";
//shared ptr take care of this dynamic allocation
	return new MyTCPServerConnection(sock,&db_rwlock,&mes_rwlock,&messages,&database);
}

