/*
 * QueryMsgDetails.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "QueryMsgDetails.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueryMsgDetails::QueryMsgDetails() {
#ifdef DEBUG
	cout << "QueryMsgDetails::QueryMsgDetails()" << endl;
#endif
	this->init();
}

QueryMsgDetails::QueryMsgDetails(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QueryMsgDetails::QueryMsgDetails(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

QueryMsgDetails::~QueryMsgDetails() {
#ifdef DEBUG
	cout << "QueryMsgDetails::~QueryMsgDetails()" << endl;
#endif
	this->destroy();
}

void QueryMsgDetails::destroy() {
	if (this->source_addr != NULL) delete this->source_addr;
	if (this->original_message_id != NULL) delete this->original_message_id;
	this->init();
}

void QueryMsgDetails::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->source_addr = NULL;
	this->original_message_id = NULL;
}

void QueryMsgDetails::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy original_message_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->original_message_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->original_message_id[i] = buffer[x+i];
	this->original_message_id[i] = 0;
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

	//Copy sm_length value
	this->sm_length = (char) buffer[x++];

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

void QueryMsgDetails::printPduInfo() {
	cout << "original_message_id = " << this->original_message_id << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			"sm_length = " << dec << (uint32_t) this->sm_length << endl;
}
