/*
 * QueryLastMsgsResp.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYLASTMSGSRESP_H_
#define QUERYLASTMSGSRESP_H_

#include "SmppBody.h"
#include "MessageDetails.h"

class QueryLastMsgsResp: public SmppBody {
public:
	QueryLastMsgsResp();
	QueryLastMsgsResp(char*, uint32_t);
	~QueryLastMsgsResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	uint8_t								number_msgs;
	MessageDetails*						message_details;
};

#endif /* QUERYLASTMSGSRESP_H_ */
