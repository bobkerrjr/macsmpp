/*
 * SubmitMultiResp.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "SubmitMultiResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

SubmitMultiResp::SubmitMultiResp() {
#ifdef DEBUG
	cout << "SubmitMultiResp::SubmitMultiResp()" << endl;
#endif
	this->init();
}

SubmitMultiResp::SubmitMultiResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "SubmitMultiResp::SubmitMultiResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

SubmitMultiResp::~SubmitMultiResp() {
#ifdef DEBUG
	cout << "SubmitMultiResp::~SubmitMultiResp()" << endl;
#endif
	this->destroy();
}

void SubmitMultiResp::destroy() {
	if (this->message_id != NULL) delete this->message_id;
	if (this->unsuccess_sme != NULL) delete [] this->unsuccess_sme;
	//TLV
	if (this->additional_status_info_text != NULL) delete this->additional_status_info_text;
	if (this->delivery_failure_reason != NULL) delete this->delivery_failure_reason;
	if (this->dpf_result != NULL) delete this->dpf_result;
	if (this->network_error_code != NULL) delete this->network_error_code;
	this->init();
}

void SubmitMultiResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->message_id = NULL;
	this->unsuccess_sme = NULL;
	//TLV
	this->additional_status_info_text = NULL;
	this->delivery_failure_reason = NULL;
	this->dpf_result = NULL;
	this->network_error_code = NULL;
}

void SubmitMultiResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i=0;
	int j=0;
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

	//Copy no_unsuccess to pduFinal
	this->no_unsuccess = buffer[x++];

	//Copy unsuccess_sme strings to pduFinal
	j = this->no_unsuccess;
	if (j==0)
		this->unsuccess_sme = NULL;
	else
		this->unsuccess_sme = (UnsuccessSme*) new UnsuccessSme[j];
	//TODO: Check if null, and treat
	if (this->unsuccess_sme != NULL)
		for(j=0;j < this->no_unsuccess;j++)
			x += this->unsuccess_sme[j].pduUnsuccessSmeDecode((char*)(buffer + x));
	else
		x++;

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
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_NETWORK_ERROR_CODE:
			this->network_error_code = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_ADDITIONAL_STATUS_INFO_TEXT:
			this->additional_status_info_text = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DPF_RESULT:
			this->dpf_result = pTemp;
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

void SubmitMultiResp::printPduInfo() {
	uint32_t i = 0;

	cout << "message_id = " << this->message_id << endl <<
			"no_unsuccess = " << dec << (uint32_t) this->no_unsuccess << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->no_unsuccess << ")" << endl;

	if (this->unsuccess_sme != NULL) {
		for(i=0; i < this->no_unsuccess; i++) {
			cout << "unsuccess_sme[" << dec << i << "]" << endl;
			this->unsuccess_sme[i].printUnsucSmeInfo();
		}
	}

	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->delivery_failure_reason != NULL) this->delivery_failure_reason->printTLVField();
	if (this->dpf_result != NULL) this->dpf_result->printTLVField();
}
