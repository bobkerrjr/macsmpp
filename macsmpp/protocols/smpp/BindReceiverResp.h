/*
 * BindReceiverResp.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDRECEIVERRESP_H_
#define BINDRECEIVERRESP_H_

#include "BindRespDummy.h"
#include <iostream>
using namespace std;

class BindReceiverResp: public BindRespDummy {
public:
	BindReceiverResp() {
#ifdef DEBUG
		cout << "BindReceiverResp::BindReceiverResp()" << endl;
#endif
		this->init();
	}
	BindReceiverResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindReceiverResp::BindReceiverResp(char* buffer, uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer,commandLength);
	}
	~BindReceiverResp() {
#ifdef DEBUG
		cout << "BindReceiverResp::~BindReceiverResp()" << endl;
#endif
	}
	void init() {
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
		BindRespDummy::init();
	}
};

#endif /* BINDRECEIVERRESP_H_ */
