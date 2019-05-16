/*
 * CancelSm.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef CANCELSM_H_
#define CANCELSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class CancelSm: public SmppBody {
public:
	CancelSm();
	CancelSm(char*, uint32_t);
	~CancelSm();
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
	TypeOfNumber						dest_addr_ton;
	NumberingPlanIndicator				dest_addr_npi;
	char*								destination_addr;
};

#endif /* CANCELSM_H_ */
