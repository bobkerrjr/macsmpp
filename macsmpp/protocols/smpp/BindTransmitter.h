/*
 * BindTransmitter.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef BINDTRANSMITTER_H_
#define BINDTRANSMITTER_H_

#include "BindDummy.h"
#include <iostream>
using namespace std;

class BindTransmitter: public BindDummy {
public:
	BindTransmitter() {
#ifdef DEBUG
		cout << "BindTransmitter::BindTransmitter()" << endl;
#endif
		this->init();
	}
	BindTransmitter(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
		cout << "BindTransmitter::BindTransmitter(char* buffer,uint32_t commandLength)" << endl;
#endif
		this->init();
		this->pduDecode(buffer, commandLength);
	}
	~BindTransmitter(){
#ifdef DEBUG
		cout << "BindTransmitter::~BindTransmitter()" << endl;
#endif
	}
	void init() {
		this->numOfByteErrors = 0;
		this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
		BindDummy::init();
	}
};

#endif /* BINDTRANSMITTER_H_ */
