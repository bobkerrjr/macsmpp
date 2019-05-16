/*
 * ParamRetrieveRespResp.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "ParamRetrieveResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

ParamRetrieveResp::ParamRetrieveResp() {
#ifdef DEBUG
	cout << "ParamRetrieveResp::ParamRetrieveResp()" << endl;
#endif
	this->init();
}

ParamRetrieveResp::ParamRetrieveResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "ParamRetrieveResp::ParamRetrieveResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

ParamRetrieveResp::~ParamRetrieveResp() {
#ifdef DEBUG
	cout << "ParamRetrieveResp::~ParamRetrieveResp()" << endl;
#endif
	this->destroy();
}

void ParamRetrieveResp::destroy() {
	if (this->param_value != NULL) delete this->param_value;
	this->init();
}

void ParamRetrieveResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->param_value = NULL;
}

void ParamRetrieveResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy param_value string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->param_value = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->param_value[i] = buffer[x+i];
	this->param_value[i] = 0;
	x+=++i;

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

void ParamRetrieveResp::printPduInfo() {
	cout << "param_name = " << this->param_value << endl;
}
