/*
 * QuerySmResp.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef QUERYSMRESP_H_
#define QUERYSMRESP_H_

#include "SmppBody.h"

class QuerySmResp: public SmppBody {
public:
	QuerySmResp();
	QuerySmResp(char*, uint32_t);
	~QuerySmResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								message_id;
	char*								final_date;
	char								message_state;
	char								error_code;
};

#endif /* QUERYSMRESP_H_ */
