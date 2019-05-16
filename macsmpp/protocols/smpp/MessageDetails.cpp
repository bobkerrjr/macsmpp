/*
 * MessageDetails.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: bobkerrjr
 */

#include "MessageDetails.h"
#include <iostream>
#include <iomanip>
using namespace std;

MessageDetails::MessageDetails() {
#ifdef DEBUG
	cout << "MessageDetails::MessageDetails()" << endl;
#endif
	this->init();
}

MessageDetails::~MessageDetails() {
#ifdef DEBUG
	cout << "MessageDetails::~MessageDetails()" << endl;
#endif
	this->destroy();
}

void MessageDetails::destroy() {
	if (this->msgid != NULL) delete this->msgid;
	this->init();
}

void MessageDetails::init() {
	//Initial values
	this->msgid = NULL;
}

uint32_t MessageDetails::pduMessageDetailsDecode(char * buffer) {
	int i = 0;
	uint32_t x = 0;

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy msgid string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->msgid = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->msgid[i] = buffer[x+i];
	this->msgid[i] = 0;
	x+=++i;

	return x;
}

void MessageDetails::printMessageDetailsInfo() {
	cout << "	msgid = " << this->msgid << endl;
}
