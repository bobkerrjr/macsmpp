/*
 * BindDummy.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#include "BindDummy.h"
#include <iostream>
#include <iomanip>
using namespace std;

BindDummy::BindDummy() {
#ifdef DEBUG
	cout << "BindDummy::BindDummy()" << endl;
#endif
	this->init();
}

BindDummy::~BindDummy() {
#ifdef DEBUG
	cout << "BindDummy::~BindDummy()" << endl;
#endif
	this->destroy();
}

void BindDummy::destroy() {
	if (this->address_range != NULL) delete this->address_range;
	if (this->password != NULL) delete this->password;
	if (this->system_id != NULL) delete this->system_id;
	if (this->system_type != NULL) delete this->system_type;
	this->init();
}

void BindDummy::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->address_range = NULL;
	this->password = NULL;
	this->system_id = NULL;
	this->system_type = NULL;
	this->addr_ton.setFieldName("addr_ton");
	this->addr_npi.setFieldName("addr_npi");
}

void BindDummy::pduDecode(char * buffer, uint32_t commandLength) {
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

	//Copy system_type string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->system_type = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->system_type[i] = buffer[x+i];
	this->system_type[i] = 0;
	x+=++i;

	this->interface_version = buffer[x++];
	this->addr_ton.setMyUnsignedByte(buffer[x++]);
	this->addr_npi.setMyUnsignedByte(buffer[x++]);

	//Copy address_range string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++; i++;
	this->address_range = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->address_range[i] = buffer[x+i];
	this->address_range[i] = 0;
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

void BindDummy::printPduInfo()
{
	cout << "system_id = " << this->system_id << endl <<
			"password = " <<  this->password << endl <<
			"system_type = " <<  this->system_type << endl <<
			"interface_version = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) this->interface_version << endl <<
			this->addr_ton << endl <<
			this->addr_npi << endl <<
			"address_range = " <<  this->address_range << endl;
}
