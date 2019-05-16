/*
 * DestinationAddress.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef DESTINATIONADDRESS_H_
#define DESTINATIONADDRESS_H_
#include "SmeOrDlAddress.h"

class DestinationAddress {
public:
	DestinationAddress();
	virtual ~DestinationAddress();
    char getDestFlag() const { return dest_flag; }
    void setDestFlag(char destFlag) { dest_flag = destFlag; }
    void init();
    void destroy();
    uint32_t pduDestAddrDecode(char *);
	void printDestAddInfo();
protected:
	uint8_t								dest_flag;
	SmeOrDlAddress*						address;
};

#endif /* DESTINATIONADDRESS_H_ */
