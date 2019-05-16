/*
 * BindTransmitterResp.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDTRANSMITTERRESP_H_
#define BINDTRANSMITTERRESP_H_

#include "BindRespDummy.h"
#include <iostream>
using namespace std;

class BindTransmitterResp: public BindRespDummy {
public:
	BindTransmitterResp() {
#ifdef DEBUG
		cout << "BindTransmitterResp::BindTransmitterResp()" << endl;
#endif
		this->init();
	}
	BindTransmitterResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindTransmitterResp::BindTransmitterResp(char* buffer, uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer,commandLength);
	}
	~BindTransmitterResp() {
#ifdef DEBUG
		cout << "BindTransmitterResp::~BindTransmitterResp()" << endl;
#endif
	}
	void init() {
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
		BindRespDummy::init();
	}
};

#endif /* BINDTRANSMITTERRESP_H_ */
