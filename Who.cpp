/*
 * Who.cpp
 *
 *  Created on: 28 lis 2014
 *      Author: edek437
 */

#include "Who.h"
#include <string.h>

Who::Who(Poco::Net::StreamSocket & sock,dbmap *in_database,Poco::RWLock *rwl) :
		Handler(sock),database(in_database), db_rwl(rwl) {
}

void Who::handle() {
	std::string answer=database_to_string(database,db_rwl);
	get_socket().sendBytes((char *) answer.c_str(), answer.size());
}

Who::~Who() {
	// TODO Auto-generated destructor stub
}

