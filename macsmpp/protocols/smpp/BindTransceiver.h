/*
 * BindTransceiver.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDTRANSCEIVER_H_
#define BINDTRANSCEIVER_H_

#include "BindDummy.h"
#include <iostream>
using namespace std;

class BindTransceiver: public BindDummy {
public:
	BindTransceiver() {
#ifdef DEBUG
		cout << "BindTransceiver::BindTransceiver()" << endl;
#endif
		this->init();
	}
	BindTransceiver(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindTransceiver::BindTransceiver(char* buffer, uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer, commandLength);
	}
	~BindTransceiver(){
#ifdef DEBUG
		cout << "BindTransceiver::~BindTransceiver()" << endl;
#endif
	}
	void init() {
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x06; // 3.4 and 5.0
		BindDummy::init();
	}
};

#endif /* BINDTRANSCEIVER_H_ */
