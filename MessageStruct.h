/*
 * structMessage.h
 *
 *  Created on: 3 gru 2014
 *      Author: edek437
 */

#ifndef MESSAGESTRUCT_H_
#define MESSAGESTRUCT_H_

#include <string>

struct MessageStruct{
	std::string receiver;
	std::string sender;
	std::string message;

	MessageStruct(std::string& r, std::string& s, std::string& m): receiver(r),sender(s),message(m){}
};



#endif /* STRUCTMESSAGE_H_ */
