/*
 * QueryBroadcastSm.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYBROADCASTSM_H_
#define QUERYBROADCASTSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class QueryBroadcastSm: public SmppBody {
public:
	QueryBroadcastSm();
	QueryBroadcastSm(char*, uint32_t);
	~QueryBroadcastSm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	//Optional TLV
	TagLengthValue*						user_message_reference;
};

#endif /* QUERYBROADCASTSM_H_ */
