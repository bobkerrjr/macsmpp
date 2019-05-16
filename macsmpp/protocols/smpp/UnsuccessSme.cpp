/*
 * UnsuccessSme.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "UnsuccessSme.h"
#include <iostream>
#include <iomanip>
using namespace std;
extern void endianSwap(uint32_t &);

UnsuccessSme::UnsuccessSme() {
#ifdef DEBUG
	cout << "UnsuccessSme::UnsuccessSme()" << endl;
#endif
	this->init();
}

UnsuccessSme::~UnsuccessSme() {
#ifdef DEBUG
	cout << "UnsuccessSme::~UnsuccessSme()" << endl;
#endif
	this->destroy();
}

void UnsuccessSme::destroy() {
	if(this->destination_addr != NULL) delete this->destination_addr;
	this->init();
}

void UnsuccessSme::init() {
	this->destination_addr = NULL;
	this->dest_addr_npi.setMyUnsignedByte(0);
	this->dest_addr_npi.setFieldName("dest_addr_npi");
	this->dest_addr_ton.setMyUnsignedByte(0);
	this->dest_addr_ton.setFieldName("dest_addr_ton");
}

uint32_t UnsuccessSme::pduUnsuccessSmeDecode(char* buffer) {
	uint32_t x = 0, i = 0;
	uint32_t* y;

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

	y = (uint32_t*) &buffer[x];
	this->error_status_code = (uint32_t) *y;
	endianSwap(this->error_status_code);
	x+=sizeof(uint32_t); //Sum size of int

	return x;
}

void UnsuccessSme::printUnsucSmeInfo() {
	cout << "	" << this->dest_addr_ton << endl <<
			"	" << this->dest_addr_npi << endl <<
			"	destination_addr = " << this->destination_addr << endl <<
			"	error_status_code = " << dec << (uint32_t) this->error_status_code << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->error_status_code << ")" << endl;
}

