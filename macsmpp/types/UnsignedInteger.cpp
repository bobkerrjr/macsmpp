/*
 * UnsignedInteger.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: bobkerrjr
 */

#include "UnsignedInteger.h"

UnsignedInteger::UnsignedInteger() {
#ifdef DEBUG
	cout << "UnsignedInteger::UnsignedInteger()" << endl;
#endif
	this->myUnsignedInteger = 0;
}

UnsignedInteger::~UnsignedInteger() {
#ifdef DEBUG
	cout << "UnsignedInteger::~UnsignedInteger()" << endl;
#endif
}

ostream& operator<< (ostream& myOStream, const UnsignedInteger& cUnsigInt) {
	myOStream << cUnsigInt.myUnsignedInteger;

	return myOStream;
}

#if defined (WINDOWS) || defined (MACOS)
void UnsignedInteger::endianSwap() {
	this->myUnsignedInteger = (this->myUnsignedInteger >> 24) |
							 ((this->myUnsignedInteger << 8) & 0x00FF0000) |
							 ((this->myUnsignedInteger >> 8) & 0x0000FF00) |
							  (this->myUnsignedInteger << 24);
}
#elif defined LINUX
    //TODO: Use cpu_to_be32
#endif
