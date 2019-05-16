/*
 * SmeAddress.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "SmeAddress.h"
#include <iostream>
#include <iomanip>
using namespace std;

SmeAddress::SmeAddress() {
#ifdef DEBUG
	cout << "SmeAddress::SmeAddress()" << endl;
#endif
	this->init();
}

SmeAddress::~SmeAddress() {
#ifdef DEBUG
	cout << "SmeAddress::~SmeAddress()" << endl;
#endif
	this->destroy();
}

void SmeAddress::destroy() {
	if (this->destination_addr != NULL) delete this->destination_addr;
	this->init();
}

void SmeAddress::init() {
	this->dest_addr_npi.setMyUnsignedByte(0);
	this->dest_addr_npi.setFieldName("dest_addr_npi");
	this->dest_addr_ton.setMyUnsignedByte(0);
	this->dest_addr_ton.setFieldName("dest_addr_ton");
	this->destination_addr = NULL;
}

uint32_t SmeAddress::pduDestAddrDecode(char* buffer) {
	uint32_t x = 0;
	int i = 0;

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	this->dest_addr_ton.setMyUnsignedByte(buffer[x++]);
	this->dest_addr_npi.setMyUnsignedByte(buffer[x++]);

	for(i=0;buffer[x+i]!=0;i++); i++;
	this->destination_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->destination_addr[i] = buffer[x+i];
	this->destination_addr[i] = 0;
	x+=++i;

	return x;
}

void SmeAddress::printDestAddInfo() {
	cout << "	" << this->dest_addr_ton << endl <<
			"	" << this->dest_addr_npi << endl <<
			"	destination_addr = " << this->destination_addr << endl;
}

