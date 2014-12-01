/*
 * Nick.cpp
 *
 *  Created on: 29 lis 2014
 *      Author: edek437
 */

#include "Nick.h"
#include "boost/regex.hpp"
#include <iostream>

Nick::Nick(Poco::Net::StreamSocket & sock, std::string& in_name_data, dbmap *in_database,Poco::RWLock *rwl) :
		Handler(sock), name_data(in_name_data), database(in_database), db_rwl(rwl) {
}

void Nick::handle() {
	boost::regex exp("<old_name>(.*)</old_name><new_name>(.*)</new_name>");
	std::string old_name=boost::regex_replace(name_data,exp,"\\1");
	std::string new_name=boost::regex_replace(name_data,exp,"\\2");
	std::cout<<"old name: "<<old_name<<std::endl;
	std::cout<<"new name: "<<new_name<<std::endl;
	bool if_changed=database_change_name(database,db_rwl, old_name, new_name);
	get_socket().sendBytes((bool *)&if_changed,sizeof(bool));
}

Nick::~Nick() {
	// TODO Auto-generated destructor stub
}

