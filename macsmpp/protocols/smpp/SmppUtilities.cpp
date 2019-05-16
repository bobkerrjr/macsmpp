/*
 * SmppUtilities.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: Bob Kerr
 */

#include "SmppUtilities.h"
#include <ctime>


char* SmppTimeDefinitions (timeFormat format) {
	struct tm *local;
	time_t t;
	char * pTemp;

	t = time(NULL);
	local = localtime(&t);
	pTemp = new char[SCHEDULE_DELIVERY_TIME_SIZE];

	return pTemp;
}
