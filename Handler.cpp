/*
 * Handler.cpp
 *
 *  Created on: 28 lis 2014
 *      Author: edek437
 */

#include "Handler.h"
#include <sstream>

//typedef std::map<std::string,Poco::Net::SocketAddress> dbmap;
Handler::Handler(Poco::Net::StreamSocket& sock): socket(sock){}

std::string Handler::database_to_string(dbmap& database,Poco::RWLock& rwl){
	std::stringstream ss;
	rwl.readLock();
	for(dbmap::iterator it=database.begin();it!=database.end();it++){
		ss<<it->first<<"::"<<it->second.toString()<<"\n";
	}
	rwl.unlock();
	return ss.str();
}

//used in not implemented yet message function
Poco::Net::SocketAddress Handler::find_address(dbmap& database,Poco::RWLock& rwl,std::string& to_find){
	Poco::Net::SocketAddress addr;
	rwl.readLock();
	dbmap::iterator mit=database.find(to_find);
	if (mit==database.end()) return addr;
	addr=mit->second;
	rwl.unlock();
	return addr;
}

bool Handler::database_change_name(dbmap& database,Poco::RWLock& rwl,const std::string& old_name,const std::string& new_name){
//no need to check if old_name not found because it is sent by client who knows his old_nick
	rwl.readLock();
	dbmap::iterator result=database.find(old_name);
	dbmap::iterator is_avaible=database.find(new_name);
	if(is_avaible!=database.end())
		return false;
	rwl.unlock();
	rwl.writeLock();
	Poco::Net::SocketAddress temp_addr=result->second;
	database.erase(result);
	database[new_name]=temp_addr;
	rwl.unlock();
	return true;
}

Poco::Net::StreamSocket Handler::get_socket(){
	return socket;
}
