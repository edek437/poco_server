/*
 * New.cpp
 *
 *  Created on: 1 gru 2014
 *      Author: edek437
 */
#include "New.h"
#include <sstream>

New::New(Poco::Net::StreamSocket & sock, std::string in_name,
		std::vector<MessageStruct> *in_vstr, Poco::RWLock *rwl) :
		Handler(sock), name(in_name), vstr(in_vstr), mes_rwl(rwl) {
	// TODO Auto-generated constructor stub

}

void New::handle() {
	std::stringstream ss;
	mes_rwl->writeLock();
	for (std::vector<MessageStruct>::iterator vit = vstr->begin();
			vit != vstr->end();) {
		if (name == vit->receiver) {
			ss << vit->sender << ":" << vit->message;
			vstr->erase(vit); //repair this in future
			break;
		}
		vit++;
	}
	mes_rwl->unlock();
	if (ss.str().empty())
		ss << "No messages";
//	std::cout<<"Sending from new to "<<name<<" letters: "<<ss.str().size()<<std::endl;
	get_socket().sendBytes((char*) ss.str().c_str(), ss.str().size());
}

New::~New() {
// TODO Auto-generated destructor stub
}

