/*
 * SubmitSmResp.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef SUBMITSMRESP_H_
#define SUBMITSMRESP_H_

#include "SmppBody.h"

class SubmitSmResp: public SmppBody {
public:
	SubmitSmResp();
	SubmitSmResp(char*, uint32_t);
	~SubmitSmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						delivery_failure_reason;
	TagLengthValue*						network_error_code;
	TagLengthValue*						additional_status_info_text;
	TagLengthValue*						dpf_result;
};

#endif /* SUBMITSMRESP_H_ */
