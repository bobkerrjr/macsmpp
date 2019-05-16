/*
 * QuerySmRespResp.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "QuerySmResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

QuerySmResp::QuerySmResp() {
#ifdef DEBUG
	cout << "QuerySmResp::QuerySmResp()" << endl;
#endif
	this->init();
}

QuerySmResp::QuerySmResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QuerySmResp::QuerySmResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

QuerySmResp::~QuerySmResp() {
#ifdef DEBUG
	cout << "QuerySmResp::~QuerySmResp()" << endl;
#endif
	this->destroy();
}

void QuerySmResp::destroy() {
	if (this->final_date != NULL) delete this->final_date;
	if (this->message_id != NULL) delete this->message_id;
	this->init();
}

void QuerySmResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->final_date = NULL;
	this->message_id = NULL;
}

void QuerySmResp::pduDecode(char* buffer, uint32_t commandLength) {
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

	//Copy final_date string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->final_date = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->final_date[i] = buffer[x+i];
	this->final_date[i] = 0;
	x+=++i;

	//Copy message_state and error_code values
	this->message_state = buffer[x++];
	this->error_code = buffer[x++];

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

void QuerySmResp::printPduInfo() {
	cout << "message_id = " << this->message_id << endl <<
			"final_date = " << this->final_date << endl <<
			"message_state = " << dec << (uint32_t) this->message_state << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->message_state << ")" << endl <<
			"error_code = " << dec << (uint32_t) this->error_code << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->error_code << ")" << endl;
}
