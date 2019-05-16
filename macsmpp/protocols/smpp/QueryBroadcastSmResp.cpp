/*
 * QueryBroadcastSmRespResp.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "QueryBroadcastSmResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueryBroadcastSmResp::QueryBroadcastSmResp() {
#ifdef DEBUG
	cout << "QueryBroadcastSmResp::QueryBroadcastSmResp()" << endl;
#endif
	this->init();
}

QueryBroadcastSmResp::QueryBroadcastSmResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QueryBroadcastSmResp::QueryBroadcastSmResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

QueryBroadcastSmResp::~QueryBroadcastSmResp() {
#ifdef DEBUG
	cout << "QueryBroadcastSmResp::~QueryBroadcastSmResp()" << endl;
#endif
	this->destroy();
}

void QueryBroadcastSmResp::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	//TLV
	if (this->broadcast_area_identifier != NULL) delete this->broadcast_area_identifier;
	if (this->broadcast_area_success != NULL) delete this->broadcast_area_success;
	if (this->broadcast_end_time != NULL) delete this->broadcast_end_time;
	if (this->message_state != NULL) delete this->message_state;
	if (this->user_message_reference != NULL) delete this->user_message_reference;
	this->init();
}

void QueryBroadcastSmResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x04; // 5.0
	this->message_id = NULL;
	//TLV
	this->broadcast_area_identifier = NULL;
	this->broadcast_area_success = NULL;
	this->broadcast_end_time = NULL;
	this->message_state = NULL;
	this->user_message_reference = NULL;
}

void QueryBroadcastSmResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy param_name string to pduFinal
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
		case TLV_BROADCAST_AREA_IDENTIFIER:
			this->broadcast_area_identifier = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_AREA_SUCCESS:
			this->broadcast_area_success = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_END_TIME:
			this->broadcast_end_time = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_MESSAGE_STATE:
			this->message_state = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_USER_MESSAGE_REFERENCE:
			this->user_message_reference = pTemp;
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

	if ((this->message_state == NULL) ||
		(this->broadcast_area_identifier == NULL) ||
		(this->broadcast_area_success == NULL))
		this->isValid = false;

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void QueryBroadcastSmResp::printPduInfo() {
	cout << "message_id = " << this->message_id << endl;

	if (this->message_state != NULL) this->message_state->printTLVField();
	if (this->broadcast_area_identifier != NULL) this->broadcast_area_identifier->printTLVField();
	if (this->broadcast_area_success != NULL) this->broadcast_area_success->printTLVField();
	if (this->broadcast_end_time != NULL) this->broadcast_end_time->printTLVField();
	if (this->user_message_reference != NULL) this->user_message_reference->printTLVField();
}
