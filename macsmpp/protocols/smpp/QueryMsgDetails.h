/*
 * QueryMsgDetails.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYMSGDETAILS_H_
#define QUERYMSGDETAILS_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class QueryMsgDetails: public SmppBody {
public:
	QueryMsgDetails();
	QueryMsgDetails(char*, uint32_t);
	~QueryMsgDetails();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								original_message_id;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	uint8_t								sm_length;
};

#endif /* QUERYMSGDETAILS_H_ */
