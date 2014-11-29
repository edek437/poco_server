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
public:
	Who(Poco::Net::StreamSocket & sock);
	void handle(dbmap& database,Poco::RWLock& rwl);
	~Who();
};

#endif /* WHO_H_ */
