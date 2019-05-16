/*
 * UnsignedInteger.h
 *
 *  Created on: Nov 8, 2011
 *      Author: bobkerrjr
 */

#ifndef UNSIGNEDINTEGER_H_
#define UNSIGNEDINTEGER_H_
#include <iomanip>
#include <iostream>
using namespace std;

class UnsignedInteger {
public:
	UnsignedInteger();
	~UnsignedInteger();
    uint32_t getMyUnsignedInteger() const { return myUnsignedInteger; }
    void setMyUnsignedInteger(uint32_t myUnsignedInteger) { this->myUnsignedInteger = myUnsignedInteger; }
    void endianSwap();
    friend ostream& operator<< (ostream& myOStream, const UnsignedInteger& cUnsigInt);
protected:
	uint32_t							myUnsignedInteger;
};

#endif /* UNSIGNEDINTEGER_H_ */
