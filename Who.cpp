/*
 * Who.cpp
 *
 *  Created on: 28 lis 2014
 *      Author: edek437
 */

#include "Who.h"
#include <string.h>

Who::Who(Poco::Net::StreamSocket & sock) :
		Handler(sock) {
}

void Who::handle(dbmap& database,Poco::RWLock& rwl) {
	std::string answer=database_to_string(database,rwl);
	get_socket().sendBytes((char *) answer.c_str(), answer.size());
}

Who::~Who() {
	// TODO Auto-generated destructor stub
}

