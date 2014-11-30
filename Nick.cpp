/*
 * Nick.cpp
 *
 *  Created on: 29 lis 2014
 *      Author: edek437
 */

#include "Nick.h"
#include "boost/regex.hpp"
#include <iostream>
#include "Get_command.h" //delete it later

Nick::Nick(Poco::Net::StreamSocket & sock, std::string& in_name_data) :
		Handler(sock), name_data(in_name_data) {
}

void Nick::handle(dbmap& database, Poco::RWLock& rwl) {
	boost::regex exp("<old_name>(.*)</old_name><new_name>(.*)</new_name>");
	std::string fmt1="\\1";
	std::string fmt2="\\2";
	std::string old_name=boost::regex_replace(name_data,exp,fmt1);
	std::string new_name=boost::regex_replace(name_data,exp,fmt2);
	std::cout<<"old name: "<<old_name<<std::endl;
	std::cout<<"new name: "<<new_name<<std::endl;
	//std::string old_name=get_command(name_data); //return old_name leave new_name in name_data, works only for names without whitespaces
	if (old_name == "default")
		old_name = get_socket().peerAddress().toString();

	bool if_changed=database_change_name(database,rwl, old_name, new_name);
	get_socket().sendBytes((bool *)&if_changed,sizeof(bool));
}

Nick::~Nick() {
	// TODO Auto-generated destructor stub
}

