/*
 * SmppPdu.h
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#ifndef SMPPPDU_H_
#define SMPPPDU_H_
#include "SmppHeader.h"
#include "SmppBody.h"

class SmppPdu {
public:
	SmppPdu();
	SmppPdu(char *);
	~SmppPdu();
	void init();
	void destroy();
	void pduDecode(char *);
	uint8_t* pduEncode();
	void printPduInfo();
	bool isVersion(uint8_t);
	bool getIsValid();
    SmppBody *getBody() const { return body; }
    SmppHeader *getHeader() const { return header; }
private:
    bool		 						isValid;
	SmppHeader* 						header;
	SmppBody*							body;
};

#endif /* SMPPPDU_H_ */
