/*
 * Nick.h
 *
 *  Created on: 29 lis 2014
 *      Author: edek437
 */

#ifndef NICK_H_
#define NICK_H_

#include "Handler.h"

class Nick: public Handler {
	std::string name_data; //old and new name here
public:
	Nick(Poco::Net::StreamSocket & sock,std::string& in_name_data);
	void handle(dbmap& database,Poco::RWLock& rwl);
	~Nick();
};

#endif /* NICK_H_ */
