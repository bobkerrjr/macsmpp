/*
 * TagLengthValue.h
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#ifndef TAGLENGTHVALUE_H_
#define TAGLENGTHVALUE_H_
#include <iostream>
#include <iomanip>
using namespace std;

class TagLengthValue {
public:
	TagLengthValue();
	TagLengthValue(char * );
	~TagLengthValue();
	void init();
	void destroy();
	void printTLVField();
	void pduDecode(char *);
    uint32_t getBufSize() const { return bufSize; }
    uint16_t getParameterTag() const { return parameterTag; }
    char* getTlvName() const { return tlvName; }
private:
    void defineTLVName();
    uint16_t 							parameterTag;
    uint16_t 							length;
    unsigned char*						value;
    char*							tlvName;
    uint32_t 							bufSize;
};

#endif /* TAGLENGTHVALUE_H_ */
