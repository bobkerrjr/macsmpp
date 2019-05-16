/*
 * SubmitMultiResp.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef SUBMITMULTIRESP_H_
#define SUBMITMULTIRESP_H_

#include "SmppBody.h"
#include "UnsuccessSme.h"

class SubmitMultiResp: public SmppBody {
public:
	SubmitMultiResp();
	SubmitMultiResp(char*, uint32_t);
	~SubmitMultiResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	uint8_t								no_unsuccess;
	UnsuccessSme*						unsuccess_sme;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						delivery_failure_reason;
	TagLengthValue*						network_error_code;
	TagLengthValue*						additional_status_info_text;
	TagLengthValue*						dpf_result;
};

#endif /* SUBMITMULTIRESP_H_ */
