/*
 * DistributionListAddress.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef DISTRIBUTIONLISTADDRESS_H_
#define DISTRIBUTIONLISTADDRESS_H_

#include "DestinationAddress.h"

class DistributionListAddress: public SmeOrDlAddress {
public:
	DistributionListAddress();
	~DistributionListAddress();
	void init();
	void destroy();
	uint32_t pduDestAddrDecode(char *);
	void printDestAddInfo();
private:
	char* 								dl_name;
};

#endif /* DISTRIBUTIONLISTADDRESS_H_ */
