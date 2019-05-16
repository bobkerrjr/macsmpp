/*
 * BroadcastSmRespResp.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "BroadcastSmResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

BroadcastSmResp::BroadcastSmResp() {
#ifdef DEBUG
	cout << "BroadcastSmResp::BroadcastSmResp()" << endl;
#endif
	this->init();
}

BroadcastSmResp::BroadcastSmResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "BroadcastSmResp::BroadcastSmResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

BroadcastSmResp::~BroadcastSmResp() {
#ifdef DEBUG
	cout << "BroadcastSmResp::~BroadcastSmResp()" << endl;
#endif
	this->destroy();
}

void BroadcastSmResp::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	//TLV
	if (this->broadcast_error_status != NULL) delete this->broadcast_error_status;
	if (this->failed_broadcast_area_identifier != NULL) delete this->failed_broadcast_area_identifier;
	this->init();
}

void BroadcastSmResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x04; // 5.0
	this->message_id = NULL;
	//TLV
	this->broadcast_error_status = NULL;
	this->failed_broadcast_area_identifier = NULL;
}

void BroadcastSmResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
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

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_BROADCAST_ERROR_STATUS:
			this->broadcast_error_status = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_AREA_IDENTIFIER:
			this->failed_broadcast_area_identifier = pTemp;
			x += pTemp->getBufSize();
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

void BroadcastSmResp::printPduInfo() {
	cout << "message_id = " << this->message_id << endl;

	if (this->broadcast_error_status != NULL) this->broadcast_error_status->printTLVField();
	if (this->failed_broadcast_area_identifier != NULL) this->failed_broadcast_area_identifier->printTLVField();
}
