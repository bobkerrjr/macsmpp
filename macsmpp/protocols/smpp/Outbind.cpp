/*
 * Outbind.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "Outbind.h"
#include <iostream>
#include <iomanip>
using namespace std;

Outbind::Outbind() {
#ifdef DEBUG
	cout << "Outbind::Outbind()" << endl;
#endif
	this->init();
}

Outbind::Outbind(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "Outbind::Outbind(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer,commandLength);
}

Outbind::~Outbind() {
#ifdef DEBUG
	cout << "Outbind::~Outbind()" << endl;
#endif
	this->destroy();
}

void Outbind::destroy() {
	if (this->password != NULL) delete this->password;
	if (this->system_id != NULL) delete this->system_id;
	this->init();
}

void Outbind::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x06; // 3.4 and 5.0
	this->password = NULL;
	this->system_id = NULL;
}

void Outbind::pduDecode(char* buffer, uint32_t commandLength) {
	int i=0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy system_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->system_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->system_id[i] = buffer[x+i];
	this->system_id[i] = 0;
	x+=++i;

	//Copy password string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->password = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->password[i] = buffer[x+i];
	this->password[i] = 0;
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

void Outbind::printPduInfo() {
	cout << "system_id = " << this->system_id << endl <<
			"password = " <<  this->password << endl;
}
