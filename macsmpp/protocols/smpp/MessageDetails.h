/*
 * MessageDetails.h
 *
 *  Created on: Nov 5, 2011
 *      Author: bobkerrjr
 */

#ifndef MESSAGEDETAILS_H_
#define MESSAGEDETAILS_H_
#include <stdint.h>

class MessageDetails {
public:
	MessageDetails();
	~MessageDetails();
	void init();
	void destroy();
	uint32_t pduMessageDetailsDecode(char *);
	void printMessageDetailsInfo();
private:
	char*							msgid;
};

#endif /* MESSAGEDETAILS_H_ */
