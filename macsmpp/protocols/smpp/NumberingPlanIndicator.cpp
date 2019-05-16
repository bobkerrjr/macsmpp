/*
 * NumberingPlanIndicator.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#include "NumberingPlanIndicator.h"
const char defaultName[] = {'n','p','i',0x00};

NumberingPlanIndicator::NumberingPlanIndicator() {
#ifdef DEBUG
	cout << "NumberingPlanIndicator::NumberingPlanIndicator()" << endl;
#endif
	this->numbering_plan_indicator_string = NULL;
	this->field_name = NULL;
}

NumberingPlanIndicator::~NumberingPlanIndicator() {
#ifdef DEBUG
	cout << "NumberingPlanIndicator::~NumberingPlanIndicator()" << endl;
#endif
	this->numbering_plan_indicator_string = NULL;
	this->field_name = NULL;
}

ostream& operator<< (ostream& myOStream, NumberingPlanIndicator& cNPI) {
	if (cNPI.field_name == NULL) cNPI.field_name = defaultName;
	myOStream << cNPI.field_name << " = 0x" << internal << hex << setw(2) << setfill('0') << (unsigned int) cNPI.myUnsignedByte << " (" << cNPI.getNPIString() << ")";

	return myOStream;
}

char* NumberingPlanIndicator::getNPIString() {
	if (numbering_plan_indicator_string == NULL) setNPIString();
	return numbering_plan_indicator_string;
}

void NumberingPlanIndicator::setNPIString() {
	switch (this->myUnsignedByte)
	{
	case 0x00:
		this->numbering_plan_indicator_string = (char*) "Unknown";
		break;
	case 0x01:
		this->numbering_plan_indicator_string = (char*) "ISDN (E163/E164)";
		break;
	case 0x03:
		this->numbering_plan_indicator_string = (char*) "Data (X.121)";
		break;
	case 0x04:
		this->numbering_plan_indicator_string = (char*) "Telex (F.69)";
		break;
	case 0x06:
		this->numbering_plan_indicator_string = (char*) "Land Mobile (E.212)";
		break;
	case 0x08:
		this->numbering_plan_indicator_string = (char*) "National";
		break;
	case 0x09:
		this->numbering_plan_indicator_string = (char*) "Private";
		break;
	case 0x0A:
		this->numbering_plan_indicator_string = (char*) "ERMES";
		break;
	case 0x0E:
		this->numbering_plan_indicator_string = (char*) "Internet (IP)";
		break;
	case 0x12:
		this->numbering_plan_indicator_string = (char*) "WAP Client Id (to be defined by WAP Forum)";
		break;
	default:
		this->numbering_plan_indicator_string = (char*) "error or reserved";
		break;
	}
}
