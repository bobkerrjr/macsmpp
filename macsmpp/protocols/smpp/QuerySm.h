/*
 * QuerySm.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYSM_H_
#define QUERYSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class QuerySm: public SmppBody {
public:
	QuerySm();
	QuerySm(char*, uint32_t);
	~QuerySm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
};

#endif /* QUERYSM_H_ */
