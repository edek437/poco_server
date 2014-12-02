/*
 * handler_factory.h
 *
 *  Created on: 2 gru 2014
 *      Author: edek437
 */

#ifndef HANDLER_FACTORY_H_
#define HANDLER_FACTORY_H_

#include "Who.h"
#include "Nick.h"
#include "Message.h"
#include "New.h"
#include "MessageDbUp.h"
#include "Get_command.h"

Handler *handler_factory(std::string str, Poco::Net::StreamSocket & sock,
		Poco::RWLock *db_rwl, Poco::RWLock *mes_rwl,
		std::map<std::string, Poco::Net::SocketAddress> *database,
		std::vector<std::string> *messages);



#endif /* HANDLER_FACTORY_H_ */
