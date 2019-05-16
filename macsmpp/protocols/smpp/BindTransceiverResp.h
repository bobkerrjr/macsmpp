/*
 * BindTransceiverResp.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDTRANSCEIVERRESP_H_
#define BINDTRANSCEIVERRESP_H_

#include "BindRespDummy.h"
#include <iostream>
using namespace std;

class BindTransceiverResp: public BindRespDummy {
public:
	BindTransceiverResp() {
#ifdef DEBUG
		cout << "BindTransceiverResp::BindTransceiverResp()" << endl;
#endif
		this->init();
	}
	BindTransceiverResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindTransceiverResp::BindTransceiverResp(char* buffer, uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer,commandLength);
	}
	~BindTransceiverResp() {
#ifdef DEBUG
		cout << "BindTransceiverResp::~BindTransceiverResp()" << endl;
#endif
	}
	void init(){
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x06; // 3.4 and 5.0
		BindRespDummy::init();
	}
};

#endif /* BINDTRANSCEIVERRESP_H_ */
