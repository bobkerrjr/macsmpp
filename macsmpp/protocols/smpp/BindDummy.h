/*
 * BindDummy.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDDUMMY_H_
#define BINDDUMMY_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class BindDummy: public SmppBody {
public:
	BindDummy();
	~BindDummy();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
protected:
	char*								system_id;
	char*								password;
	char*								system_type;
	uint8_t								interface_version;
	TypeOfNumber						addr_ton;
	NumberingPlanIndicator				addr_npi;
	char*								address_range;
};

#endif /* BINDDUMMY_H_ */
