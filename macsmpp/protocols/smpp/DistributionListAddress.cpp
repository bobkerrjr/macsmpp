
/*
 * DistributionListAddress.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "DistributionListAddress.h"
#include <iostream>
#include <iomanip>
using namespace std;

DistributionListAddress::DistributionListAddress() {
#ifdef DEBUG
	cout << "DistributionListAddress::DistributionListAddress()" << endl;
#endif
	this->init();
}

DistributionListAddress::~DistributionListAddress() {
#ifdef DEBUG
	cout << "DistributionListAddress::~DistributionListAddress()" << endl;
#endif
	this->destroy();
}

void DistributionListAddress::destroy() {
	if (this->dl_name != NULL) delete this->dl_name;
	this->init();
}

void DistributionListAddress::init() {
	this->dl_name = NULL;
}


uint32_t DistributionListAddress::pduDestAddrDecode(char* buffer) {
	int i = 0;
	uint32_t x = 0;

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	for(i=0;buffer[x+i]!=0;i++); i++;
	this->dl_name = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->dl_name[i] = buffer[x+i];
	this->dl_name[i] = 0;
	x+=++i;

	return x;
}

void DistributionListAddress::printDestAddInfo() {
	cout << "	dl_name = " << this->dl_name << endl;
}

