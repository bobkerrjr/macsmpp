/*
 * CancelBroadcastSm.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef CANCELBROADCASTSM_H_
#define CANCELBROADCASTSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class CancelBroadcastSm: public SmppBody {
public:
	CancelBroadcastSm();
	CancelBroadcastSm(char*, uint32_t);
	~CancelBroadcastSm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								service_type;
	char*								message_id;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	//Optional TLV
	TagLengthValue*						broadcast_content_type;
	TagLengthValue*						user_message_reference;
};

#endif /* CANCELBROADCASTSM_H_ */
