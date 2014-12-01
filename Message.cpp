/*
 * Message.cpp
 *
 *  Created on: 30 lis 2014
 *      Author: edek437
 */

#include "Message.h"
#include <iostream>
#include <Poco/Exception.h>

Message::Message(Poco::Net::StreamSocket & sock, std::string& in_name, dbmap *in_database, Poco::RWLock *rwl) :
		Handler(sock), name(in_name),  database(in_database), db_rwl(rwl){
}

void Message::handle() {
	bool is_addr = find_address(database, db_rwl, name);
	std::string b;
	is_addr ? b="TRUE" : b="FALSE";
	std::cout << "Sending to client: " <<b << std::endl;
	get_socket().sendBytes((bool *) &is_addr, sizeof(bool));
	std::cout << "Exiting message\n";
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

