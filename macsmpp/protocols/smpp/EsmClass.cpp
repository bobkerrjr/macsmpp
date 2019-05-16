/*
 * EsmClass.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#include "EsmClass.h"
const char defaultName[] = {'e','s','m','_','c','l','a','s','s',0x00};

EsmClass::EsmClass() {
#ifdef DEBUG
	cout << "EsmClass::EsmClass()" << endl;
#endif
	this->messageFlow = 0x00;
	this->esm_class_gsm_specific_string = NULL;
	this->esm_class_messaging_mode_string = NULL;
	this->esm_class_messaging_type_string = NULL;
	this->field_name = NULL;
}

EsmClass::~EsmClass() {
#ifdef DEBUG
	cout << "EsmClass::~EsmClass()" << endl;
#endif
	this->esm_class_gsm_specific_string = NULL;
	this->esm_class_messaging_mode_string = NULL;
	this->esm_class_messaging_type_string = NULL;
	this->field_name = NULL;
}

ostream& operator<< (ostream& myOStream, EsmClass& cESMClass) {
	if (cESMClass.field_name == NULL) cESMClass.field_name = defaultName;
	myOStream << cESMClass.field_name << " = 0x" << internal << hex << setw(2) << setfill('0') << (unsigned int) cESMClass.myUnsignedByte << endl;
	myOStream << cESMClass.field_name << " = " << cESMClass.getESMClassMessagingModeString() << endl;
	myOStream << cESMClass.field_name << " = " << cESMClass.getESMClassMessagingTypeString() << endl;
	myOStream << cESMClass.field_name << " = " << cESMClass.getESMClassGsmSpecificString();

	return myOStream;
}

char* EsmClass::getESMClassMessagingModeString() {
	if (esm_class_messaging_mode_string == NULL) setESMClassMessagingModeString();
	return esm_class_messaging_mode_string;
}

char* EsmClass::getESMClassMessagingTypeString() {
	if (esm_class_messaging_type_string == NULL) setESMClassMessagingTypeString();
	return esm_class_messaging_type_string;
}

char* EsmClass::getESMClassGsmSpecificString() {
	if (esm_class_gsm_specific_string == NULL) setESMClassGsmSpecificString();
	return esm_class_gsm_specific_string;
}

//Messaging Mode (bits 1-0)
void EsmClass::setESMClassMessagingModeString() {
	if (this->messageFlow == 0x01)
	{
		switch ((this->myUnsignedByte & 0x03))
		{
		case 0x00:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 0 0 - Default SMSC Mode";
			break;
		case 0x01:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 0 1 - Datagram mode";
			break;
		case 0x02:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 1 0 - Forward mode";
			break;
		case 0x03:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 1 1 - Store and Forward mode";
			break;
		}
	}
	else if (this->messageFlow == 0x02)
	{
		this->esm_class_messaging_mode_string = (char*) "x x x x x x x x  - not applicable";
	}
	else
	{
		switch ((this->myUnsignedByte & 0x03))
		{
		case 0x00:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 0 0";
			break;
		case 0x01:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 0 1";
			break;
		case 0x02:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 1 0";
			break;
		case 0x03:
			this->esm_class_messaging_mode_string = (char*) "x x x x x x 1 1";
			break;
		}
	}
}

//Message Type (bits 5-2)
void EsmClass::setESMClassMessagingTypeString() {
	if (this->messageFlow == 0x01)
	{
		switch ((this->myUnsignedByte & 0x3C))
		{
		case 0x00:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 0 x x - Default message Type";
			break;
		case 0x04:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 1 x x - reserved";
			break;
		case 0x08:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 0 x x - Short Message contains ESME Delivery Acknowledgement";
			break;
		case 0x0C:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 1 x x - reserved";
			break;
		case 0x10:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 0 x x - Short Message contains ESME Manual/User Acknowledgement";
			break;
		case 0x14:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 1 x x - reserved";
			break;
		case 0x18:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 0 x x - reserved";
			break;
		case 0x1C:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 1 x x - reserved";
			break;
		case 0x20:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 0 x x - reserved";
			break;
		case 0x24:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 1 x x - reserved";
			break;
		case 0x28:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 0 x x - reserved";
			break;
		case 0x2C:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 1 x x - reserved";
			break;
		case 0x30:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 0 x x - reserved";
			break;
		case 0x34:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 1 x x - reserved";
			break;
		case 0x38:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 0 x x - reserved";
			break;
		case 0x3C:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 1 x x - reserved";
			break;
		}
	}
	else if (this->messageFlow == 0x02)
	{
		switch ((this->myUnsignedByte & 0x3C))
		{
		case 0x00:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 0 x x - Default message Type";
			break;
		case 0x04:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 1 x x - Short Message contains SMSC Delivery Receipt";
			break;
		case 0x08:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 0 x x - Short Message contains SME Delivery Acknowledgement";
			break;
		case 0x0C:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 1 x x - reserved";
			break;
		case 0x10:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 0 x x - Short Message contains SME Manual/User Acknowledgment";
			break;
		case 0x14:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 1 x x - reserved";
			break;
		case 0x18:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 0 x x - Short Message contains Conversation Abort (Korean CDMA)";
			break;
		case 0x1C:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 1 x x - reserved";
			break;
		case 0x20:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 0 x x - Short Message contains Intermediate Delivery Notification";
			break;
		case 0x24:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 1 x x - reserved";
			break;
		case 0x28:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 0 x x - reserved";
			break;
		case 0x2C:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 1 x x - reserved";
			break;
		case 0x30:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 0 x x - reserved";
			break;
		case 0x34:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 1 x x - reserved";
			break;
		case 0x38:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 0 x x - reserved";
			break;
		case 0x3C:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 1 x x - reserved";
			break;
		}
	}
	else
	{
		switch ((this->myUnsignedByte & 0x3C))
		{
		case 0x00:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 0 x x";
			break;
		case 0x04:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 0 1 x x";
			break;
		case 0x08:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 0 x x";
			break;
		case 0x0C:
			this->esm_class_messaging_type_string = (char*) "x x 0 0 1 1 x x";
			break;
		case 0x10:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 0 x x";
			break;
		case 0x14:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 0 1 x x";
			break;
		case 0x18:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 0 x x";
			break;
		case 0x1C:
			this->esm_class_messaging_type_string = (char*) "x x 0 1 1 1 x x";
			break;
		case 0x20:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 0 x x";
			break;
		case 0x24:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 0 1 x x";
			break;
		case 0x28:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 0 x x";
			break;
		case 0x2C:
			this->esm_class_messaging_type_string = (char*) "x x 1 0 1 1 x x";
			break;
		case 0x30:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 0 x x";
			break;
		case 0x34:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 0 1 x x";
			break;
		case 0x38:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 0 x x";
			break;
		case 0x3C:
			this->esm_class_messaging_type_string = (char*) "x x 1 1 1 1 x x";
			break;
		}
	}
}

//GSM Network Specific Features (bits 7-6)
void EsmClass::setESMClassGsmSpecificString() {
	if (this->messageFlow == 0x01)
	{
		switch ((this->myUnsignedByte & 0xC0))
		{
		case 0x00:
			this->esm_class_gsm_specific_string = (char*) "0 0 x x x x x x - No specific features selected";
			break;
		case 0x40:
			this->esm_class_gsm_specific_string = (char*) "0 1 x x x x x x - UDHI Indicator";
			break;
		case 0x80:
			this->esm_class_gsm_specific_string = (char*) "1 0 x x x x x x - Set Reply Path";
			break;
		case 0xC0:
			this->esm_class_gsm_specific_string = (char*) "1 1 x x x x x x - Set UDHI and Reply Path";
			break;
		}
	}
	else if (this->messageFlow == 0x02)
	{
		switch ((this->myUnsignedByte & 0xC0))
		{
		case 0x00:
			this->esm_class_gsm_specific_string = (char*) "0 0 x x x x x x - No specific features selected";
			break;
		case 0x40:
			this->esm_class_gsm_specific_string = (char*) "0 1 x x x x x x - UDHI Indicator set";
			break;
		case 0x80:
			this->esm_class_gsm_specific_string = (char*) "1 0 x x x x x x - Reply Path";
			break;
		case 0xC0:
			this->esm_class_gsm_specific_string = (char*) "1 1 x x x x x x - UDHI and Reply Path";
			break;
		}
	}
	else
	{
		switch ((this->myUnsignedByte & 0xC0))
		{
		case 0x00:
			this->esm_class_gsm_specific_string = (char*) "0 0 x x x x x x";
			break;
		case 0x40:
			this->esm_class_gsm_specific_string = (char*) "0 1 x x x x x x";
			break;
		case 0x80:
			this->esm_class_gsm_specific_string = (char*) "1 0 x x x x x x";
			break;
		case 0xC0:
			this->esm_class_gsm_specific_string = (char*) "1 1 x x x x x x";
			break;
		}
	}
}

