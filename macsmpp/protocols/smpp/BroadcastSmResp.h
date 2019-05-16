/*
 * BroadcastSmResp.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef BROADCASTSMRESP_H_
#define BROADCASTSMRESP_H_

#include "SmppBody.h"

class BroadcastSmResp: public SmppBody {
public:
	BroadcastSmResp();
	BroadcastSmResp(char*, uint32_t);
	~BroadcastSmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	//Optional TLV
	TagLengthValue*						broadcast_error_status;
	TagLengthValue*						failed_broadcast_area_identifier;
};

#endif /* BROADCASTSMRESP_H_ */
