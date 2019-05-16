/*
 * SmeOrDlAddress.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef SMEORDLADDRESS_H_
#define SMEORDLADDRESS_H_
#include <stdint.h>

class SmeOrDlAddress {
public:
	SmeOrDlAddress();
	virtual ~SmeOrDlAddress();
	virtual void init() = 0;
	virtual uint32_t pduDestAddrDecode(char*) = 0;
	virtual void printDestAddInfo() = 0;
};

#endif /* SMEORDLADDRESS_H_ */
