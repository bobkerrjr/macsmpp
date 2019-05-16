/*
 * SmppHeader.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#include "SmppHeader.h"
#include "CommandId.h"
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
extern void endianSwap(uint32_t &);

SmppHeader::SmppHeader() {
#ifdef DEBUG
	cout << "SmppHeader::SmppHeader()" << endl;
#endif
	this->init();
}

SmppHeader::SmppHeader(char * buffer) {
#ifdef DEBUG
	cout << "SmppHeader::SmppHeader(char * buffer)" << endl;
#endif
	this->init();
	this->pduDecode(buffer);
}

SmppHeader::~SmppHeader() {
#ifdef DEBUG
		cout << "SmppHeader::~SmppHeader()" << endl;
#endif
	}

void SmppHeader::init() {
	command_length = 0;
	command_id.setMyUnsignedInteger(0);
	command_status.setMyUnsignedInteger(0);
	sequence_number = 0;
}

void SmppHeader::destroy() {
	this->init();
}

void SmppHeader::pduDecode(char* buffer) {
	uint32_t* x = NULL;

	x = (uint32_t*) buffer;

	//Decode command_length and swap big endian to little endian
	command_length = (uint32_t) *x;
	endianSwap(command_length);
	x++;

	//Decode command_id and swap big endian to little endian
	command_id.setMyUnsignedInteger((uint32_t) *x);
	command_id.endianSwap();
	x++;

	//Decode command_status and swap big endian to little endian
	command_status.setMyUnsignedInteger((uint32_t) *x);
	command_status.endianSwap();
	x++;

	//Decode sequence_number and swap big endian to little endian
	sequence_number = (uint32_t) *x;
	endianSwap(sequence_number);
}

void SmppHeader::pduEncode(uint8_t* buffer) {
	uint32_t* x = NULL;
	uint32_t temp;

	x = (uint32_t*) buffer;

	//Encode command_length and swap little endian to big endian
	temp = command_length;
	endianSwap(temp);
	*x=temp;
	x++;

	//Encode command_id and swap little endian to big endian
	temp = command_id.getMyUnsignedInteger();
	endianSwap(temp);
	*x=temp;
	x++;

	//Encode command_status and swap little endian to big endian
	temp = command_status.getMyUnsignedInteger();
	endianSwap(temp);
	*x=temp;
	x++;

	//Encode sequence_number and swap little endian to big endian
	temp = sequence_number;
	endianSwap(temp);
	*x=temp;
}

void SmppHeader::printPduInfo() {
	ostringstream oTemp;

	//Print header for all type of PDU
	oTemp << "command_length = " << dec << command_length << " (0x" << internal << setw(8) << setfill('0') << hex << command_length << ")" << endl <<
			  command_id << endl <<
			  command_status << endl <<
			 "sequence_number = " << dec << sequence_number << " (0x" << internal << setw(8) << setfill('0') << hex << sequence_number << ")" << endl;

	cout << oTemp.str();
}

bool SmppHeader::isVersion(uint8_t version) {
	bool vTemp = false;

	//Check if the header possible version is equal to 'version'
	switch(this->command_id.getMyUnsignedInteger())
	{
	case ESME_PARAM_RETRIEVE:				//3.3
	case ESME_PARAM_RETRIEVE_RESP:			//3.3
	case ESME_QUERY_LAST_MSGS:				//3.3
	case ESME_QUERY_LAST_MSGS_RESP:			//3.3
	case ESME_QUERY_MSG_DETAILS:			//3.3
	case ESME_QUERY_MSG_DETAILS_RESP:		//3.3
		vTemp = ((version == 0x33) || (version != 0x34) || (version != 0x50)) ? true : false;
		break;
	case ESME_SUBMIT_SM:					//3.3		3.4			5.0
	case ESME_SUBMIT_SM_RESP:				//3.3		3.4			5.0
	case SMSC_DELIVER_SM:					//3.3		3.4			5.0
	case SMSC_DELIVER_SM_RESP:				//3.3		3.4			5.0
	case BOTH_UBD:							//3.3		3.4			5.0
	case BOTH_UBD_RESP:						//3.3		3.4			5.0
	case ESME_BND_RECEIVER: 				//3.3		3.4			5.0
	case ESME_BND_RECEIVER_RESP: 			//3.3		3.4			5.0
	case ESME_BND_TRANSMITTER:				//3.3		3.4			5.0
	case ESME_BND_TRANSMITTER_RESP:			//3.3		3.4			5.0
	case BOTH_QRYLINK:						//3.3		3.4			5.0
	case BOTH_QRYLINK_RESP:					//3.3		3.4			5.0
	case ESME_DATA_SM:						//3.3		3.4			5.0
	case ESME_DATA_SM_RESP:					//3.3		3.4			5.0
	case ESME_QUERY_SM:						//3.3		3.4			5.0
	case ESME_QUERY_SM_RESP:				//3.3		3.4			5.0
	case ESME_SUBMIT_MULTI:					//3.3		3.4			5.0
	case ESME_SUBMIT_MULTI_RESP:			//3.3		3.4			5.0
	case BOTH_GENERIC_NACK: 				//3.3		3.4			5.0
	case ESME_REPLACE_SM:					//3.3		3.4			5.0
	case ESME_REPLACE_SM_RESP:				//3.3		3.4			5.0
	case ESME_CANCEL_SM:					//3.3		3.4			5.0
	case ESME_CANCEL_SM_RESP:				//3.3		3.4			5.0
	case SMSC_ALERT_NOT:					//3.3		3.4			5.0
		vTemp = ((version == 0x33) || (version == 0x34) || (version == 0x50)) ? true : false;
		break;
	case ESME_BND_TRANSCEIVER:				//			3.4			5.0
	case ESME_BND_TRANSCEIVER_RESP:			//			3.4			5.0
	case SMSC_OUTBD:						//			3.4			5.0
		vTemp = ((version != 0x33) || (version == 0x34) || (version == 0x50)) ? true : false;
		break;
	case ESME_BCAST_SM:						//						5.0
	case ESME_BCAST_SM_RESP:				//						5.0
	case ESME_QUERY_BCAST_SM:				//						5.0
	case ESME_QUERY_BCAST_SM_RESP:			//						5.0
	case ESME_CANCEL_BCAST_SM:				//						5.0
	case ESME_CANCEL_BCAST_SM_RESP:			//						5.0
		vTemp = ((version != 0x33) || (version != 0x34) || (version == 0x50)) ? true : false;
		break;
	default:
		vTemp = false;
		break;
	}

	return vTemp;
}
