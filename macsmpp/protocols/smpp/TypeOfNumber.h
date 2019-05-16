/*
 * TypeOfNumber.h
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#ifndef TYPEOFNUMBER_H_
#define TYPEOFNUMBER_H_

#include "../../types/UnsignedByte.h"

class TypeOfNumber: public UnsignedByte {
public:
	TypeOfNumber();
	~TypeOfNumber();
    char* getTONString();
    void setTONString();
    friend ostream& operator<< (ostream& myOStream, TypeOfNumber& cTON);
    const char *getFieldName() const { return field_name; }
    void setFieldName(const char *fieldName) { field_name = fieldName; }
protected:
    char*							type_of_number_string;
    const char*						field_name;
};

#endif /* TYPEOFNUMBER_H_ */
