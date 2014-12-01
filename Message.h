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
	dbmap *database;
	Poco::RWLock *db_rwl;
public:
	Message(Poco::Net::StreamSocket & sock, std::string& in_name, dbmap *database, Poco::RWLock *rwl);
	void handle();
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
