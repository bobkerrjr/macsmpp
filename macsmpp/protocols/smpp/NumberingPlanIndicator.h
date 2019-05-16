/*
 * NumberingPlanIndicator.h
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#ifndef NUMBERINGPLANINDICATOR_H_
#define NUMBERINGPLANINDICATOR_H_

#include "../../types/UnsignedByte.h"

class NumberingPlanIndicator: public UnsignedByte {
public:
	NumberingPlanIndicator();
	~NumberingPlanIndicator();
    char* getNPIString();
    void setNPIString();
    friend ostream& operator<< (ostream& myOStream, NumberingPlanIndicator& cNPI);
    const char *getFieldName() const { return field_name; }
    void setFieldName(const char *fieldName) { field_name = fieldName; }
protected:
    char*									numbering_plan_indicator_string;
    const char*								field_name;
};

#endif /* NUMBERINGPLANINDICATOR_H_ */
