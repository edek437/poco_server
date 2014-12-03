/*
 * handler_factory.cpp
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#include "handler_factory.h"

Handler *handler_factory(std::string str, Poco::Net::StreamSocket & sock,
		Poco::RWLock *db_rwl, Poco::RWLock *mes_rwl,
		std::map<std::string, Poco::Net::SocketAddress> *database,
		std::vector<MessageStruct> *messages) {
	std::string command = get_command(str);
	if (command == "who") {
		return new Who(sock,database, db_rwl);
	} else if (command == "nick") {
		return new Nick(sock, str,database,db_rwl);
	} else if (command == "msg") {
		return new Message(sock, str,database,db_rwl);
	} else if (command == "msg2") {
		return new MessageDbUp(sock, str,messages,mes_rwl);
	} else if (command == "new") {
		return new New(sock,str,messages, mes_rwl);
	} else
		return NULL;
}
