/*
 * Who.h
 *
 *  Created on: 28 lis 2014
 *      Author: edek437
 */

#ifndef WHO_H_
#define WHO_H_

#include "Handler.h"

class Who: public Handler {
	dbmap *database;
	Poco::RWLock  *db_rwl;
public:
	Who(Poco::Net::StreamSocket & sock,dbmap *database,Poco::RWLock *rwl);
	void handle();
	~Who();
};

#endif /* WHO_H_ */
