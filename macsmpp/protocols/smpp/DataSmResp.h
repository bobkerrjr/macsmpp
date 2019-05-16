/*
 * DataSmResp.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef DATASMRESP_H_
#define DATASMRESP_H_

#include "SmppBody.h"

class DataSmResp: public SmppBody {
public:
	DataSmResp();
	DataSmResp(char*, uint32_t);
	~DataSmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	//Optional TLV - Supported on both 3.4 and 5.0
	TagLengthValue*						delivery_failure_reason;
	TagLengthValue*						network_error_code;
	TagLengthValue*						additional_status_info_text;
	TagLengthValue*						dpf_result;
};

#endif /* DATASMRESP_H_ */
