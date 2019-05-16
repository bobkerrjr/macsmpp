/*
 * QueryMsgDetailsResp.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYMSGDETAILSRESP_H_
#define QUERYMSGDETAILSRESP_H_

#include "SmppBody.h"
#include "DestinationAddress.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class QueryMsgDetailsResp: public SmppBody {
public:
	QueryMsgDetailsResp();
	QueryMsgDetailsResp(char*, uint32_t);
	~QueryMsgDetailsResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								service_type;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	uint8_t								number_of_dests;
	DestinationAddress*					dest_address;
	uint8_t								protocol_id;
	uint8_t								priority_flag;
	char*								schedule_delivery_time;
	char*								validity_period;
	uint8_t								registered_delivery_flag;
	uint8_t								data_coding;
	uint8_t								sm_length;
	char*								short_message;
	char*								msgid;
	char*								final_date;
	uint8_t								message_status;
	uint8_t								error_code;
};

#endif /* QUERYMSGDETAILSRESP_H_ */
