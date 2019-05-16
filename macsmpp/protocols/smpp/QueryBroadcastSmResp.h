/*
 * QueryBroadcastSmResp.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYBROADCASTSMRESP_H_
#define QUERYBROADCASTSMRESP_H_

#include "SmppBody.h"

class QueryBroadcastSmResp: public SmppBody {
public:
	QueryBroadcastSmResp();
	QueryBroadcastSmResp(char*, uint32_t);
	~QueryBroadcastSmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	//Mandatory TLV
	TagLengthValue*						message_state;
	TagLengthValue*						broadcast_area_identifier;
	TagLengthValue*						broadcast_area_success;
	//Optional TLV
	TagLengthValue*						broadcast_end_time;
	TagLengthValue*						user_message_reference;
};

#endif /* QUERYBROADCASTSMRESP_H_ */
