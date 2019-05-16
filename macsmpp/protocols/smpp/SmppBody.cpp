/*
 * SmppBody.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#include "SmppBody.h"
#include <iostream>
using namespace std;

SmppBody::SmppBody( ) {
#ifdef DEBUG
	cout << "SmppBody::SmppBody()" << endl;
#endif
	numOfByteErrors = 0;
	isValid = true;
	myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
}

SmppBody::~SmppBody( ) {
#ifdef DEBUG
	cout << "SmppBody::~SmppBody()" << endl;
#endif
}

bool SmppBody::isVersion(uint8_t version) {
	if (version == 0x33)
		return ((this->myPossibleVersion & 0x01) && 0x01) ? true : false;
	else if (version == 0x34)
		return ((this->myPossibleVersion & 0x02) && 0x02) ? true : false;
	else if (version == 0x50)
		return ((this->myPossibleVersion & 0x04) && 0x04) ? true : false;
	else return false;
}
