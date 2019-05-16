/*
 * CancelSm.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "CancelSm.h"
#include <iostream>
#include <iomanip>
using namespace std;

CancelSm::CancelSm() {
#ifdef DEBUG
	cout << "CancelSm::CancelSm()" << endl;
#endif
	this->init();
}

CancelSm::CancelSm(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "CancelSm::CancelSm(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

CancelSm::~CancelSm() {
#ifdef DEBUG
	cout << "CancelSm::~CancelSm()" << endl;
#endif
	this->destroy();
}

void CancelSm::destroy() {
	if (this->destination_addr != NULL) delete this->destination_addr;
	if (this->message_id != NULL) delete this->message_id;
	if (this->service_type != NULL) delete this->service_type;
	if (this->source_addr != NULL) delete this->source_addr;
	this->init();
}

void CancelSm::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->dest_addr_ton.setFieldName("dest_addr_ton");
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->dest_addr_npi.setFieldName("dest_addr_npi");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->destination_addr = NULL;
	this->message_id = NULL;
	this->service_type = NULL;
	this->source_addr = NULL;
}

void CancelSm::pduDecode(char* buffer, uint32_t commandLength) {
	int i=0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy service_type string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->service_type = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->service_type[i] = buffer[x+i];
	this->service_type[i] = 0;
	x+=++i;

	//Copy message_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->message_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->message_id[i] = buffer[x+i];
	this->message_id[i] = 0;
	x+=++i;

	//Copy ton and npi values
	this->source_addr_ton.setMyUnsignedByte((char) buffer[x++]);
	this->source_addr_npi.setMyUnsignedByte((char) buffer[x++]);

	//Copy source_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->source_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->source_addr[i] = buffer[x+i];
	this->source_addr[i] = 0;
	x+=++i;

	//Copy ton and npi values
	this->dest_addr_ton.setMyUnsignedByte((char) buffer[x++]);
	this->dest_addr_npi.setMyUnsignedByte((char) buffer[x++]);

	//Copy destination_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->destination_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->destination_addr[i] = buffer[x+i];
	this->destination_addr[i] = 0;
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

void CancelSm::printPduInfo() {
	cout << "service_type = " << this->service_type << endl <<
			"message_id = " << this->message_id << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			this->dest_addr_ton << endl <<
			this->dest_addr_npi << endl <<
			"destination_addr = " << this->destination_addr << endl;
}
