/*
 * QueryLastMsgs.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYLASTMSGS_H_
#define QUERYLASTMSGS_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class QueryLastMsgs: public SmppBody {
public:
	QueryLastMsgs();
	QueryLastMsgs(char*, uint32_t);
	~QueryLastMsgs();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	uint8_t								num_messages;
};

#endif /* QUERYLASTMSGS_H_ */
