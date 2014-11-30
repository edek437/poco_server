/*
 * Message.h
 *
 *  Created on: 30 lis 2014
 *      Author: edek437
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Handler.h"

class Message: public Handler {
	std::string name;
public:
	Message(Poco::Net::StreamSocket & sock, std::string& in_name);
	void handle(dbmap& database, Poco::RWLock& rwl);
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
