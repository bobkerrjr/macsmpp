/*
 * SmppHeader.h
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#ifndef SMPPHEADER_H_
#define SMPPHEADER_H_
#include <stdint.h>
#include "CommandStatus.h"
#include "CommandId.h"

class SmppHeader {
public:
	SmppHeader();
	SmppHeader(char *);
	~SmppHeader();
	void init();
	void destroy();
	void pduDecode(char *);
	void pduEncode(uint8_t *);
	void printPduInfo();
	bool isVersion(uint8_t);
    uint32_t getCommandId() const { return command_id.getMyUnsignedInteger(); }
    uint32_t getCommandLength() const { return command_length; }
    uint32_t getCommandStatus() const { return command_status.getMyUnsignedInteger(); }
    uint32_t getSequenceNumber() const { return sequence_number; }
    void setCommandId(uint32_t commandId) { command_id.setMyUnsignedInteger(commandId); }
    void setCommandLength(uint32_t commandLength) { command_length = commandLength; }
    void setCommandStatus(uint32_t commandStatus) { command_status.setMyUnsignedInteger(commandStatus); }
    void setSequenceNumber(uint32_t sequenceNumber) { sequence_number = sequenceNumber; }
private:
	uint32_t							command_length;			//defines the total octet length of the SMPP PDU packet including the length field
	CommandId							command_id;				//identifies the particular SMPP PDU
	CommandStatus						command_status;			//indicates the success or failure of an SMPP request
	uint32_t							sequence_number;		//contains a sequence number which allows SMPP requests and responses to be associated for correlation purposes
};

#endif /* SMPPHEADER_H_ */
