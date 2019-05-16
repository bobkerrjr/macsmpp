/*
 * ParamRetrieve.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "ParamRetrieve.h"
#include <iostream>
#include <iomanip>
using namespace std;

ParamRetrieve::ParamRetrieve() {
#ifdef DEBUG
	cout << "ParamRetrieve::ParamRetrieve()" << endl;
#endif
	this->init();
}

ParamRetrieve::ParamRetrieve(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "ParamRetrieve::ParamRetrieve(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

ParamRetrieve::~ParamRetrieve() {
#ifdef DEBUG
	cout << "ParamRetrieve::~ParamRetrieve()" << endl;
#endif
	this->destroy();
}

void ParamRetrieve::destroy() {
	if (this->param_name != NULL) delete this->param_name;
	this->init();
}

void ParamRetrieve::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->param_name = NULL;
}

void ParamRetrieve::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy param_name string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->param_name = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->param_name[i] = buffer[x+i];
	this->param_name[i] = 0;
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

void ParamRetrieve::printPduInfo() {
	cout << "param_name = " << this->param_name << endl;
}
