/*
 * New.h
 *
 *  Created on: 1 gru 2014
 *      Author: edek437
 */

#ifndef NEW_H_
#define NEW_H_

#include "Handler.h"

class New: public Handler {
	std::string name;
	std::vector<std::string> *vstr;
	Poco::RWLock *mes_rwl;
public:
	New(Poco::Net::StreamSocket & sock,std::string in_name, std::vector<std::string> *in_vstr, Poco::RWLock *rwl);
	void handle();
	virtual ~New();
};

#endif /* NEW_H_ */
