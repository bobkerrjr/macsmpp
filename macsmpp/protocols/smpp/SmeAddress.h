/*
 * SmeAddress.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef SMEADDRESS_H_
#define SMEADDRESS_H_

#include "DestinationAddress.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class SmeAddress: public SmeOrDlAddress {
public:
	SmeAddress();
	~SmeAddress();
	void init();
	void destroy();
	uint32_t pduDestAddrDecode(char *);
	void printDestAddInfo();
private:
	TypeOfNumber						dest_addr_ton;
	NumberingPlanIndicator				dest_addr_npi;
	char*								destination_addr;
};

#endif /* SMEADDRESS_H_ */
