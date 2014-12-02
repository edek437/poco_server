/*
 * server_framework.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: ztp
 */

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Exception.h"
#include "MyTCPServerConnectionFactory.h"

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
