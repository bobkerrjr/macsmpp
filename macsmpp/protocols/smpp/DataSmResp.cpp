/*
 * DataSmRespResp.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "DataSmResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

DataSmResp::DataSmResp() {
#ifdef DEBUG
	cout << "DataSmResp::DataSmResp()" << endl;
#endif
	this->init();
}

DataSmResp::DataSmResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "DataSmResp::DataSmResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

DataSmResp::~DataSmResp() {
#ifdef DEBUG
	cout << "DataSmResp::~DataSmResp()" << endl;
#endif
	this->destroy();
}

void DataSmResp::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	//TLV
	if (this->additional_status_info_text != NULL) delete this->additional_status_info_text;
	if (this->delivery_failure_reason != NULL) delete this->delivery_failure_reason;
	if (this->dpf_result != NULL) delete this->dpf_result;
	if (this->network_error_code != NULL) delete this->network_error_code;
	this->init();
}

void DataSmResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->message_id = NULL;
	//TLV
	this->additional_status_info_text = NULL;
	this->delivery_failure_reason = NULL;
	this->dpf_result = NULL;
	this->network_error_code = NULL;
}

void DataSmResp::pduDecode(char* buffer, uint32_t commandLength) {
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

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_DELIVERY_FAILURE_REASON:
			this->delivery_failure_reason = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_NETWORK_ERROR_CODE:
			this->network_error_code = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_ADDITIONAL_STATUS_INFO_TEXT:
			this->additional_status_info_text = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_DPF_RESULT:
			this->dpf_result = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
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

void DataSmResp::printPduInfo() {
	cout << "message_id = " << this->message_id << endl;

	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->dpf_result != NULL) this->dpf_result->printTLVField();
}
