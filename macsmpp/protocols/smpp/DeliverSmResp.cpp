/*
 * DeliverSmResp.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "DeliverSmResp.h"
#include <iomanip>
#include <iostream>
using namespace std;


DeliverSmResp::DeliverSmResp(){
#ifdef DEBUG
	cout << "DeliverSmResp::DeliverSmResp()" << endl;
#endif
	this->init();
}


DeliverSmResp::DeliverSmResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "DeliverSmResp::DeliverSmResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}


DeliverSmResp::~DeliverSmResp() {
#ifdef DEBUG
	cout << "DeliverSmResp::~DeliverSmResp()" << endl;
#endif
	this->destroy();
}

void DeliverSmResp::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	//TLV
	if (this->additional_status_info_text != NULL) delete this->additional_status_info_text;
	if (this->delivery_failure_reason != NULL) delete this->delivery_failure_reason;
	if (this->network_error_code != NULL) delete this->network_error_code;
	this->init();
}

void DeliverSmResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->message_id = NULL;
	//TLV
	this->additional_status_info_text = NULL;
	this->delivery_failure_reason = NULL;
	this->network_error_code = NULL;
}

void DeliverSmResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Initial values
	this->message_id = NULL;

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
		case TLV_ADDITIONAL_STATUS_INFO_TEXT:
			this->additional_status_info_text = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DELIVERY_FAILURE_REASON:
			this->delivery_failure_reason = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_NETWORK_ERROR_CODE:
			this->network_error_code = pTemp;
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


void DeliverSmResp::printPduInfo() {
	cout << "message_id = " << this->message_id << endl;

	if (this->additional_status_info_text != NULL) this->additional_status_info_text->printTLVField();
	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->network_error_code != NULL) this->network_error_code->printTLVField();
}
