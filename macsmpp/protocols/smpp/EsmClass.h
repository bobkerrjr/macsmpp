/*
 * EsmClass.h
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#ifndef ESMCLASS_H_
#define ESMCLASS_H_

#include "../../types/UnsignedByte.h"
#include "CommandId.h"

class EsmClass: public UnsignedByte {
public:
	EsmClass();
	~EsmClass();
    char* getESMClassMessagingModeString();
    void setESMClassMessagingModeString();
    char* getESMClassMessagingTypeString();
    void setESMClassMessagingTypeString();
    char* getESMClassGsmSpecificString();
    void setESMClassGsmSpecificString();
    friend ostream& operator<< (ostream& myOStream, EsmClass& cESMClass);
    char getMessageFlow() const { return messageFlow; }
    void setMessageFlow(char messageFlow) { this->messageFlow = messageFlow; }
    bool isFromEsmeToSmsc() const { return from_esme_to_smsc; }
    void setFromEsmeToSmsc(bool fromEsmeToSmsc) { from_esme_to_smsc = fromEsmeToSmsc; }
    const char *getFieldName() const { return field_name; }
    void setFieldName(const char *fieldName) { field_name = fieldName; }
protected:
    char							messageFlow; //00 - default, 01 - TX, 02 - RX
    char*							esm_class_messaging_mode_string;
    char*							esm_class_messaging_type_string;
    char*							esm_class_gsm_specific_string;
    const char*						field_name;
    bool							from_esme_to_smsc;
};

#endif /* ESMCLASS_H_ */
