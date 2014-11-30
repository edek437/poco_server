/*
 * Message.cpp
 *
 *  Created on: 30 lis 2014
 *      Author: edek437
 */

#include "Message.h"
#include <iostream>

Message::Message(Poco::Net::StreamSocket & sock, std::string& in_name) :
		Handler(sock), name(in_name) {
}

void Message::handle(dbmap& database, Poco::RWLock& rwl) {
	Poco::Net::SocketAddress addr = find_address(database, rwl, name);
	std::cout<<"Sending to client: "<<addr.toString()<<std::endl;
	get_socket().sendBytes((char *) addr.toString().c_str(),addr.toString().size());
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

