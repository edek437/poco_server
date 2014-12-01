/*
 * MessageDbUp.cpp
 *
 *  Created on: 1 gru 2014
 *      Author: edek437
 */

#include "MessageDbUp.h"

MessageDbUp::MessageDbUp(Poco::Net::StreamSocket& sock, std::string& in_message,
		std::vector<std::string> *in_vstr, Poco::RWLock *rwl) :
		Handler(sock), message(in_message), vstr(in_vstr), mes_rwl(rwl) {
	// TODO Auto-generated constructor stub
}

void MessageDbUp::handle() {
	mes_rwl->writeLock();
	vstr->push_back(message);
	mes_rwl->unlock();
	bool b=true;
	get_socket().sendBytes((bool*)&b,sizeof(bool));
}

MessageDbUp::~MessageDbUp() {
	// TODO Auto-generated destructor stub
}

