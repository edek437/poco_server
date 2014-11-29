/*
 * Handler.h
 *
 *  Created on: 28 lis 2014
 *      Author: edek437
 */
#include <map>
#include "Poco/Net/SocketAddress.h"
#include "Poco/RWLock.h"
#include "Poco/Net/StreamSocket.h"

#ifndef HANDLER_H_
#define HANDLER_H_

class Handler {
	Poco::Net::StreamSocket socket;
public:
	typedef std::map<std::string,Poco::Net::SocketAddress> dbmap;

	Handler(Poco::Net::StreamSocket& socket);
	virtual void handle(dbmap& database,Poco::RWLock& rwl)=0;
	void database_change_name(dbmap& database,Poco::RWLock& rwl ,const std::string& old_name,const std::string& new_name);
	std::string database_to_string(dbmap& database,Poco::RWLock& rwl);
	const Poco::Net::SocketAddress find_address(dbmap& database,Poco::RWLock& rwl,std::string& to_find);
	Poco::Net::StreamSocket get_socket();
	virtual ~Handler() {
	}
	;
};



#endif /* HANDLER_H_ */
