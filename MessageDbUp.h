/*
 * MessageDbUp.h
 *
 *  Created on: 1 gru 2014
 *      Author: edek437
 */

#ifndef MESSAGEDBUP_H_
#define MESSAGEDBUP_H_

#include "Handler.h"

class MessageDbUp: public Handler {
	std::string message;
	std::vector<std::string> *vstr;
	Poco::RWLock *mes_rwl;
public:
	MessageDbUp(Poco::Net::StreamSocket& sock, std::string& message,
			std::vector<std::string> *in_vstr, Poco::RWLock *rwl);
	void handle();
	virtual ~MessageDbUp();
};

#endif /* MESSAGEDBUP_H_ */
