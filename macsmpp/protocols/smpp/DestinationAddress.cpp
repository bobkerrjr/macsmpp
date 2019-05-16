/*
 * DestinationAddress.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "DestinationAddress.h"
#include "DistributionListAddress.h"
#include "SmeAddress.h"
#include <iostream>
#include <iomanip>
using namespace std;

DestinationAddress::DestinationAddress() {
#ifdef DEBUG
	cout << "DestinationAddress::DestinationAddress()" << endl;
#endif
	this->init();
}

DestinationAddress::~DestinationAddress() {
#ifdef DEBUG
	cout << "DestinationAddress::~DestinationAddress()" << endl;
#endif
	this->destroy();
}

void DestinationAddress::destroy() {
	if (this->address != NULL) delete this->address;
	this->init();
}

void DestinationAddress::init() {
	this->dest_flag = 0;
	this->address = NULL;
}

uint32_t DestinationAddress::pduDestAddrDecode(char * buffer) {
	uint32_t x=0;

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	this->dest_flag = buffer[x++];
	if (this->dest_flag == 1) //SME Address
	{
		SmeAddress* pTemp = NULL;
		pTemp = new SmeAddress();
		this->address = dynamic_cast<SmeOrDlAddress*>(pTemp);
		x += this->address->pduDestAddrDecode(buffer+x);
	}
	else if (this->dest_flag == 2) //Distribution List
	{
		DistributionListAddress* pTemp = NULL;
		pTemp = new DistributionListAddress();
		this->address = dynamic_cast<SmeOrDlAddress*>(pTemp);
		x += this->address->pduDestAddrDecode((char*)(buffer + x));
	}
	return x;
}
void DestinationAddress::printDestAddInfo() {
	cout << "	dest_flag = " << dec << (uint32_t) this->dest_flag << endl;
	this->address->printDestAddInfo();
}

