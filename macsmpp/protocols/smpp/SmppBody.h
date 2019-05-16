/*
 * SmppBody.h
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#ifndef SMPPBODY_H_
#define SMPPBODY_H_

#include "TagLengthValue.h"
#include "optionalParameterTagDef.h"

class SmppBody {
public:
	SmppBody( );
	virtual ~SmppBody( );
	virtual void init() = 0;
	virtual void destroy() = 0;
    virtual void pduDecode(char*, uint32_t) = 0;
    //virtual void pduEncode(uint8_t*) = 0;
    virtual void printPduInfo() = 0;
    bool isVersion(uint8_t);
    uint32_t getNumOfByteErrors() const { return numOfByteErrors; }
    void setNumOfByteErrors(uint32_t numOfByteErrors) { this->numOfByteErrors = numOfByteErrors; }
    bool getIsValid() const { return this->isValid; }
protected:
    bool isValid;
    uint32_t numOfByteErrors;
    uint8_t myPossibleVersion;
};

#endif /* SMPPBODY_H_ */
