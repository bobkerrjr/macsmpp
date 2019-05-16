/*
 * ParamRetrieve.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef PARAMRETRIEVE_H_
#define PARAMRETRIEVE_H_

#include "SmppBody.h"

class ParamRetrieve: public SmppBody {
public:
	ParamRetrieve();
	ParamRetrieve(char*, uint32_t);
	~ParamRetrieve();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								param_name;
};

#endif /* PARAMRETRIEVE_H_ */
