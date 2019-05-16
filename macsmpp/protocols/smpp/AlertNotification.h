/*
 * AlertNotification.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef ALERTNOTIFICATION_H_
#define ALERTNOTIFICATION_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class AlertNotification: public SmppBody {
public:
	AlertNotification();
	AlertNotification(char*, uint32_t);
	~AlertNotification();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	TypeOfNumber						esme_addr_ton;
	NumberingPlanIndicator				esme_addr_npi;
	char*								esme_addr;
	//Optional TLV - Supported on both 3.4 and 5.0
	TagLengthValue*						ms_availability_status;
};

#endif /* ALERTNOTIFICATION_H_ */
