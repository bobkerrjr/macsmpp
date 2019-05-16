/*
 * UnsignedByte.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: bobkerrjr
 */

#include "UnsignedByte.h"

UnsignedByte::UnsignedByte() {
#ifdef DEBUG
	cout << "UnsignedByte::UnsignedByte()" << endl;
#endif
	this->myUnsignedByte = 0;
}

UnsignedByte::~UnsignedByte() {
#ifdef DEBUG
	cout << "UnsignedByte::~UnsignedByte()" << endl;
#endif
}

ostream& operator<< (ostream& myOStream, const UnsignedByte& cUnsigByte) {
	myOStream << cUnsigByte.myUnsignedByte;

	return myOStream;
}
