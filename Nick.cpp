/*
 * Nick.cpp
 *
 *  Created on: 29 lis 2014
 *      Author: edek437
 */

#include "Nick.h"
#include "Get_command.h"
#include <iostream>

Nick::Nick(Poco::Net::StreamSocket & sock, std::string& in_name_data) :
		Handler(sock), name_data(in_name_data) {
}

void Nick::handle(dbmap& database, Poco::RWLock& rwl) {
	std::string old_name=get_command(name_data); //return old_name leave new_name in name_data
	if (old_name == "default")
		old_name = get_socket().peerAddress().toString();

	database_change_name(database,rwl, old_name, name_data);
	std::string answer="nick changed";
	get_socket().sendBytes((char *) answer.c_str(), answer.size());
}

Nick::~Nick() {
	// TODO Auto-generated destructor stub
}

