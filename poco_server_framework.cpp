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
#include "Poco/Util/ServerApplication.h"
#include <iostream>

//TODO: figure out what going on and comment it

class MyTCPServerConnection: public Poco::Net::TCPServerConnection{
private:
//TODO: static database for info about connections(handler, IP, port, name)

public:
	MyTCPServerConnection(const Poco::Net::StreamSocket & sock): Poco::Net::TCPServerConnection(sock){}

//TODO: what is run doing
	void run(){
		char buffer[100];
		std::cout<<"running"<<std::endl;
//TODO: put receive to function and do some mutex stuff with it
		int len=socket().receiveBytes((char *)buffer,sizeof(buffer));
		buffer[len]='\0';
		std::cout<<buffer<<std::endl;

	}

	~MyTCPServerConnection(){
		std::cout<<"ending connection"<<std::endl;
	}
};


class MyTCPServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory{
public:
	Poco::Net::TCPServerConnection* createConnection( const Poco::Net::StreamSocket & sock){
		std::cout<<"create connection\n";
//shared ptr take care of this dynamic allocation
		return new MyTCPServerConnection(sock);
	}
};

int main(int argc, char** argv){
	Poco::Net::TCPServerConnectionFactory::Ptr pTSCF= new MyTCPServerConnectionFactory(); //Ptr is hared pointer here
	Poco::Net::ServerSocket ser_sock(8080); //bind+listen
	Poco::Net::TCPServer server(pTSCF,ser_sock);
	server.start();
	while(1){}
	server.stop();
	return 0;
}
