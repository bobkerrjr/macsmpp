/*
 * BindReceiver.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDRECEIVER_H_
#define BINDRECEIVER_H_

#include "BindDummy.h"
#include <iostream>
using namespace std;

class BindReceiver: public BindDummy {
public:
	BindReceiver(){
#ifdef DEBUG
		cout << "BindReceiver::BindReceiver()" << endl;
#endif
		this->init();
	}
	BindReceiver(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindReceiver::BindReceiver(char* buffer, uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer, commandLength);
	}
	~BindReceiver(){
#ifdef DEBUG
		cout << "BindReceiver::~BindReceiver()" << endl;
#endif
	}
	void init() {
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
		BindDummy::init();
	}
};

#endif /* BINDRECEIVER_H_ */
