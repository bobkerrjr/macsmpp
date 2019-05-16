/*
 * QueryLastMsgs.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "QueryLastMsgs.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueryLastMsgs::QueryLastMsgs() {
#ifdef DEBUG
	cout << "QueryLastMsgs::QueryLastMsgs()" << endl;
#endif
	this->init();
}

QueryLastMsgs::QueryLastMsgs(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QueryLastMsgs::QueryLastMsgs(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

QueryLastMsgs::~QueryLastMsgs() {
#ifdef DEBUG
	cout << "QueryLastMsgs::~QueryLastMsgs()" << endl;
#endif
	this->destroy();
}

void QueryLastMsgs::destroy() {
	if (this->source_addr != NULL) delete this->source_addr;
	this->init();
}

void QueryLastMsgs::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->source_addr = NULL;
}

void QueryLastMsgs::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

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

	//Copy num_messages value
	this->num_messages = (char) buffer[x++];

	//Check if exist any optional parameter
	/* Version 3.3 of SMPP does not support TLV
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
	*/

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void QueryLastMsgs::printPduInfo() {
	cout << this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			"num_messages = " << dec << (uint32_t) this->num_messages << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->num_messages << ")" << endl;
}
