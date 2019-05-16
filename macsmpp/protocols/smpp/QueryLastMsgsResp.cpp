/*
 * QueryLastMsgsRespResp.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "QueryLastMsgsResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueryLastMsgsResp::QueryLastMsgsResp() {
#ifdef DEBUG
	cout << "QueryLastMsgsResp::QueryLastMsgsResp()" << endl;
#endif
	this->init();
}

QueryLastMsgsResp::QueryLastMsgsResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QueryLastMsgsResp::QueryLastMsgsResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

QueryLastMsgsResp::~QueryLastMsgsResp() {
#ifdef DEBUG
	cout << "QueryLastMsgsResp::~QueryLastMsgsResp()" << endl;
#endif
	this->destroy();
}

void QueryLastMsgsResp::destroy() {
	if (this->message_details != NULL) delete [] this->message_details;
	this->init();
}

void QueryLastMsgsResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->message_details = NULL;
}

void QueryLastMsgsResp::pduDecode(char * buffer, uint32_t commandLength) {
	int j = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy number_msgs value
	this->number_msgs = (char) buffer[x++];

	//Copy message_details strings to pduFinal
	j = this->number_msgs;
	if (j==0)
		this->message_details = NULL;
	else
		this->message_details = (MessageDetails*) new MessageDetails[j];
	//TODO: Check if null, and treat
	if (this->message_details != NULL)
		for(j=0;j < this->number_msgs;j++)
			x += this->message_details[j].pduMessageDetailsDecode((char*)(buffer + x));
	else
		x++;

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

void QueryLastMsgsResp::printPduInfo() {
	int i = 0;
	cout << "number_msgs = " << dec << (uint32_t) this->number_msgs << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->number_msgs << ")" << endl;

	if (this->message_details != NULL) {
		for(i=0; i < this->number_msgs; i++) {
			cout << "message_details[" << dec << i << "]" << endl;
			this->message_details[i].printMessageDetailsInfo();
		}
	}
}
