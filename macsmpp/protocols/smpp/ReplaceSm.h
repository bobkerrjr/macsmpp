/*
 * ReplaceSm.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef REPLACESM_H_
#define REPLACESM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class ReplaceSm: public SmppBody {
public:
	ReplaceSm();
	ReplaceSm(char*, uint32_t);
	~ReplaceSm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	char*								schedule_delivery_time;
	char*								validity_period;
	uint8_t								registered_delivery;
	uint8_t								sm_default_msg_id;
	uint8_t								sm_length;
	char*								short_message;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						message_payload;
};

#endif /* REPLACESM_H_ */
