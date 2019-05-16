/*
 * QuerySm.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "QuerySm.h"
#include <iostream>
#include <iomanip>
using namespace std;

QuerySm::QuerySm() {
#ifdef DEBUG
	cout << "QuerySm::QuerySm()" << endl;
#endif
	this->init();
}

QuerySm::QuerySm(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QuerySm::QuerySm(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

QuerySm::~QuerySm() {
#ifdef DEBUG
	cout << "QuerySm::~QuerySm()" << endl;
#endif
	this->destroy();
}

void QuerySm::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	if (this->source_addr != NULL) delete this->source_addr;
	this->init();
}

void QuerySm::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->message_id = NULL;
	this->source_addr = NULL;
}

void QuerySm::pduDecode(char* buffer, uint32_t commandLength) {
	int i=0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy message_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->message_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->message_id[i] = buffer[x+i];
	this->message_id[i] = 0;
	x+=++i;

	//Copy ton and npi values
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

void QuerySm::printPduInfo() {
	cout << "message_id = " << this->message_id << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl;
}
