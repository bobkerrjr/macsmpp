/*
 * AlertNotification.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "AlertNotification.h"
#include <iostream>
#include <iomanip>
using namespace std;

AlertNotification::AlertNotification() {
#ifdef DEBUG
	cout << "AlertNotification::AlertNotification()" << endl;
#endif
	this->init();
}

AlertNotification::AlertNotification(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "AlertNotification::AlertNotification(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

AlertNotification::~AlertNotification() {
#ifdef DEBUG
	cout << "AlertNotification::~AlertNotification()" << endl;
#endif
	this->destroy();
}

void AlertNotification::destroy() {
	if (this->esme_addr != NULL) delete this->esme_addr;
	if (this->source_addr != NULL) delete this->source_addr;
	//TLV
	if (this->ms_availability_status != NULL) delete this->ms_availability_status;
	this->init();
}

void AlertNotification::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->esme_addr_ton.setFieldName("esme_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->esme_addr_npi.setFieldName("esme_addr_npi");
	this->esme_addr = NULL;
	this->source_addr = NULL;
	//TLV
	this->ms_availability_status = NULL;
}

void AlertNotification::pduDecode(char* buffer, uint32_t commandLength) {
	int i=0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy ton and npi to pduFinal
	this->source_addr_ton.setMyUnsignedByte(buffer[x++]);
	this->source_addr_npi.setMyUnsignedByte(buffer[x++]);

	//Copy source_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->source_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->source_addr[i] = buffer[x+i];
	this->source_addr[i] = 0;
	x+=++i;

	//Copy ton and npi to pduFinal
	this->esme_addr_ton.setMyUnsignedByte(buffer[x++]);
	this->esme_addr_npi.setMyUnsignedByte(buffer[x++]);

	//Copy esme_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->esme_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->esme_addr[i] = buffer[x+i];
	this->esme_addr[i] = 0;
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
		case TLV_MS_AVAILABILITY_STATUS:
			this->ms_availability_status = pTemp;
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

void AlertNotification::printPduInfo() {
	cout << this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			this->esme_addr_ton << endl <<
			this->esme_addr_npi << endl <<
			"esme_addr = " << this->esme_addr << endl;

	if (this->ms_availability_status != NULL) this->ms_availability_status->printTLVField();
}
