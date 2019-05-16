/*
 * Outbind.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef OUTBIND_H_
#define OUTBIND_H_

#include "SmppBody.h"

class Outbind: public SmppBody {
public:
	Outbind();
	Outbind(char*, uint32_t);
	~Outbind();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								system_id;
	char*								password;
};

#endif /* OUTBIND_H_ */
