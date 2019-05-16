/*
 * DeliverSmResp.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef DELIVERSMRESP_H_
#define DELIVERSMRESP_H_

#include "SmppBody.h"


class DeliverSmResp: public SmppBody {
public:
	DeliverSmResp();
	DeliverSmResp(char*, uint32_t);
	~DeliverSmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						additional_status_info_text;
	TagLengthValue*						delivery_failure_reason;
	TagLengthValue*						network_error_code;
};

#endif /* DELIVERSMRESP_H_ */
