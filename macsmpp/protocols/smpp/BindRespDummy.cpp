/*
 * BindRespDummy.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#include "BindRespDummy.h"
#include <iostream>
#include <iomanip>
using namespace std;


BindRespDummy::BindRespDummy() {
#ifdef DEBUG
	cout << "BindRespDummy::BindRespDummy()" << endl;
#endif
	this->init();
}

BindRespDummy::~BindRespDummy() {
#ifdef DEBUG
	cout << "BindRespDummy::~BindRespDummy()" << endl;
#endif
	this->destroy();
}

void BindRespDummy::destroy() {
	if (this->system_id != NULL) delete this->system_id;
	//TLV
	if (this->sc_interface_version != NULL) delete this->sc_interface_version;
	this->init();
}

void BindRespDummy::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->system_id = NULL;
	//TLV
	this->sc_interface_version = NULL;
}

void BindRespDummy::pduDecode(char * buffer,uint32_t commandLength) {
	int i=0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy system_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++; i++;
	this->system_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->system_id[i] = buffer[x+i];
	this->system_id[i] = 0;
	x+=++i;

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_SC_INTERFACE_VERSION:
			this->sc_interface_version = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		default:
			x += pTemp->getBufSize();
			this->numOfByteErrors += pTemp->getBufSize();
#ifdef DEBUG
			cout << "Discarded pTemp->parameterTag = 0x" << internal << setw(4) << setfill('0') << hex << pTemp->getParameterTag() << " - " << pTemp->getTlvName() << endl;
#endif
			delete pTemp;
			this->isValid = false;
			//TODO: Treat error
			break;
		}
		pTemp = NULL;
	}

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void BindRespDummy::printPduInfo() {
	cout << "system_id = " << this->system_id << endl;

	if (this->sc_interface_version != NULL) this->sc_interface_version->printTLVField();
}
