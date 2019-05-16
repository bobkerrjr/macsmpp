/*
 * UnsignedByte.h
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#ifndef UNSIGNEDBYTE_H_
#define UNSIGNEDBYTE_H_
#include <iomanip>
#include <iostream>
using namespace std;

class UnsignedByte {
public:
	UnsignedByte();
	~UnsignedByte();
	uint8_t getMyUnsignedByte() const { return myUnsignedByte; }
    void setMyUnsignedByte(uint8_t myUnsignedByte) { this->myUnsignedByte = myUnsignedByte; }
    friend ostream& operator<< (ostream& myOStream, const UnsignedByte& cUnsigByte);
protected:
    uint8_t							myUnsignedByte;
};

#endif /* UNSIGNEDBYTE_H_ */
