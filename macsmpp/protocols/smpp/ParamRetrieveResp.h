/*
 * ParamRetrieveResp.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef PARAMRETRIEVERESP_H_
#define PARAMRETRIEVERESP_H_

#include "SmppBody.h"

class ParamRetrieveResp: public SmppBody {
public:
	ParamRetrieveResp();
	ParamRetrieveResp(char*, uint32_t);
	~ParamRetrieveResp();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								param_value;
};

#endif /* PARAMRETRIEVERESP_H_ */
