/*
 * ReplaceSm.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "ReplaceSm.h"
#include <iostream>
#include <iomanip>
using namespace std;

ReplaceSm::ReplaceSm() {
#ifdef DEBUG
	cout << "ReplaceSm::ReplaceSm()" << endl;
#endif
	this->init();
}

ReplaceSm::ReplaceSm(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "ReplaceSm::ReplaceSm(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

ReplaceSm::~ReplaceSm() {
#ifdef DEBUG
	cout << "ReplaceSm::~ReplaceSm()" << endl;
#endif
	this->destroy();
}

void ReplaceSm::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	if (this->schedule_delivery_time != NULL) delete this->schedule_delivery_time;
	if (this->short_message != NULL) delete this->short_message;
	if (this->source_addr != NULL) delete this->source_addr;
	if (this->validity_period != NULL) delete this->validity_period;
	//TLV
	if (this->message_payload != NULL) delete this->message_payload;
	this->init();
}

void ReplaceSm::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->message_id = NULL;
	this->schedule_delivery_time = NULL;
	this->short_message = NULL;
	this->source_addr = NULL;
	this->validity_period = NULL;
	//TLV
	this->message_payload = NULL;
}

void ReplaceSm::pduDecode(char* buffer, uint32_t commandLength) {
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

	//Copy schedule_delivery_time string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->schedule_delivery_time = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->schedule_delivery_time[i] = buffer[x+i];
	this->schedule_delivery_time[i] = 0;
	x+=++i;

	//Copy validity_period string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->validity_period = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->validity_period[i] = buffer[x+i];
	this->validity_period[i] = 0;
	x+=++i;

	//Copy registered_delivery, sm_default_msg_id and sm_length values
	this->registered_delivery = (char) buffer[x++];
	this->sm_default_msg_id = (char) buffer[x++];
	this->sm_length = (char) buffer[x++];

	//Copy short_message string to pduFinal
	i = this->sm_length;
	if (i==0)
		this->short_message = NULL;
	else
		this->short_message = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;i < this->sm_length;i++)
		this->short_message[i] = buffer[x+i];
	x+=this->sm_length;

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_MESSAGE_PAYLOAD:
			this->message_payload = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
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

void ReplaceSm::printPduInfo() {
	int i;
	cout << "message_id = " << this->message_id << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			"schedule_delivery_time = " << this->schedule_delivery_time << endl <<
			"validity_period = " << this->validity_period << endl <<
			"registered_delivery = " << dec << (uint32_t) this->registered_delivery << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->registered_delivery << ")" << endl <<
			"sm_default_msg_id = " << dec << (uint32_t) this->sm_default_msg_id << " (0x" << internal << hex << setw(2) << setfill('0')  << (uint32_t) this->sm_default_msg_id << ")" << endl <<
			"sm_length = " << dec << (uint32_t) this->sm_length << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->sm_length << ")" << endl;
	cout << "short_message = ";
	for(i=0; i < this->sm_length; i++)
		cout << this->short_message[i];
	cout << endl;

	if (this->message_payload != NULL) this->message_payload->printTLVField();
}
