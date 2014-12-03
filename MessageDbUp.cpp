/*
 * MessageDbUp.cpp
 *
 *  Created on: 1 gru 2014
 *      Author: edek437
 */

#include "MessageDbUp.h"
#include "boost/regex.hpp"

MessageDbUp::MessageDbUp(Poco::Net::StreamSocket& sock, std::string& in_message,
		std::vector<MessageStruct> *in_vstr, Poco::RWLock *rwl) :
		Handler(sock), message(in_message), vstr(in_vstr), mes_rwl(rwl) {
	// TODO Auto-generated constructor stub
}

void MessageDbUp::handle() {
	std::string regex =
			"<receiver>(.*)</receiver><sender>(.*)</sender><message>(.*)</message>";
	boost::regex exp(regex);
	std::string rec = boost::regex_replace(message, exp, "\\1");
	std::string send = boost::regex_replace(message, exp, "\\2");
	std::string mes = boost::regex_replace(message, exp, "\\3");
	mes_rwl->writeLock();
	vstr->push_back(MessageStruct(rec, send, mes));
	mes_rwl->unlock();
	bool b = true;
	get_socket().sendBytes((bool*) &b, sizeof(bool));
}

MessageDbUp::~MessageDbUp() {
	// TODO Auto-generated destructor stub
}

