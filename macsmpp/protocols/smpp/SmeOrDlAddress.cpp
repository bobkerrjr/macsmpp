/*
 * SmeOrDlAddress.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#include "SmeOrDlAddress.h"
#include <iostream>
using namespace std;

SmeOrDlAddress::SmeOrDlAddress() {
#ifdef DEBUG
	cout << "SmeOrDlAddress::SmeOrDlAddress()" << endl;
#endif
}

SmeOrDlAddress::~SmeOrDlAddress() {
#ifdef DEBUG
	cout << "SmeOrDlAddress::~SmeOrDlAddress()" << endl;
#endif
}
