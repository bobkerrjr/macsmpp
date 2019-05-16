/*
 * TypeOfNumber.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#include "TypeOfNumber.h"
const char defaultName[] = {'t','o','n',0x00};

TypeOfNumber::TypeOfNumber() {
#ifdef DEBUG
	cout << "TypeOfNumber::TypeOfNumber()" << endl;
#endif
	this->type_of_number_string = NULL;
	this->field_name = NULL;
}

TypeOfNumber::~TypeOfNumber() {
#ifdef DEBUG
	cout << "TypeOfNumber::~TypeOfNumber()" << endl;
#endif
	this->type_of_number_string = NULL;
	this->field_name = NULL;
}

ostream& operator<< (ostream& myOStream, TypeOfNumber& cTON) {
	if (cTON.field_name == NULL) cTON.field_name = defaultName;
	myOStream << cTON.field_name << " = 0x" << internal << hex << setw(2) << setfill('0') << (unsigned int) cTON.myUnsignedByte << " (" << cTON.getTONString() << ")";

	return myOStream;
}

char* TypeOfNumber::getTONString() {
	if (type_of_number_string == NULL) setTONString();
	return type_of_number_string;
}

void TypeOfNumber::setTONString() {
	switch (this->myUnsignedByte)
	{
	case 0x00:
		this->type_of_number_string = (char*) "Unknown";
		break;
	case 0x01:
		this->type_of_number_string = (char*) "International";
		break;
	case 0x02:
		this->type_of_number_string = (char*) "National";
		break;
	case 0x03:
		this->type_of_number_string = (char*) "Network Specific";
		break;
	case 0x04:
		this->type_of_number_string = (char*) "Subscriber Number";
		break;
	case 0x05:
		this->type_of_number_string = (char*) "Alphanumeric";
		break;
	case 0x06:
		this->type_of_number_string = (char*) "Abbreviated";
		break;
	default:
		this->type_of_number_string = (char*) "error or reserved";
		break;
	}
}
