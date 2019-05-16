/*
 * UnsuccessSme.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef UNSUCCESSSME_H_
#define UNSUCCESSSME_H_
#include <stdint.h>
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class UnsuccessSme {
public:
	UnsuccessSme();
	~UnsuccessSme();
	void init();
	void destroy();
	uint32_t pduUnsuccessSmeDecode(char *);
	void printUnsucSmeInfo();
private:
	TypeOfNumber						dest_addr_ton;
	NumberingPlanIndicator				dest_addr_npi;
	char* 								destination_addr;
	uint32_t 							error_status_code;
};

#endif /* UNSUCCESSSME_H_ */
