/*
 * BindRespDummy.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDRESPDUMMY_H_
#define BINDRESPDUMMY_H_

#include "SmppBody.h"
#include <iostream>
using namespace std;

class BindRespDummy: public SmppBody {
public:
	BindRespDummy();
	virtual ~BindRespDummy();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
protected:
	char*								system_id;
	//Optional TLV - Supported on both 3.4 and 5.0
	TagLengthValue* 					sc_interface_version;
};

#endif /* BINDRESPDUMMY_H_ */
