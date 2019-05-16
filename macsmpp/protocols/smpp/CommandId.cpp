/*
 * CommandId.cpp
 *
 *  Created on: 07/11/2011
 *      Author: Bob Kerr
 */

#include "CommandId.h"

CommandId::CommandId() {
#ifdef DEBUG
	cout << "CommandId::CommandId()" << endl;
#endif
	this->command_id_string = NULL;
	this->full_command_id_string = NULL;
}

CommandId::~CommandId() {
#ifdef DEBUG
	cout << "CommandId::~CommandId()" << endl;
#endif
	this->command_id_string = NULL;
	this->full_command_id_string = NULL;
}

ostream& operator<< (ostream& myOStream, CommandId& cCmdId) {
	myOStream << "command_status = 0x" << internal << setw(8) << setfill('0') << hex << cCmdId.myUnsignedInteger << " (" << cCmdId.getCommandIdString() << ")";

	return myOStream;
}

char* CommandId::getCommandIdString() {
	if (command_id_string == NULL) setCommandIdString();
	return command_id_string;
}

char* CommandId::getFullCommandIdString() {
	if (full_command_id_string == NULL) getFullCommandIdString();
	return full_command_id_string;
}

void CommandId::setCommandIdString() {
	switch (this->myUnsignedInteger)
	{
	case ESME_SUBMIT_SM:					//3.3		3.4			5.0
		this->command_id_string = (char*) "submit_sm";
		break;
	case ESME_SUBMIT_SM_RESP:				//3.3		3.4			5.0
		this->command_id_string = (char*) "submit_sm_resp";
		break;
	case SMSC_DELIVER_SM:					//3.3		3.4			5.0
		this->command_id_string = (char*) "deliver_sm";
		break;
	case SMSC_DELIVER_SM_RESP:				//3.3		3.4			5.0
		this->command_id_string = (char*) "deliver_sm_resp";
		break;
	case BOTH_UBD:							//3.3		3.4			5.0
		this->command_id_string = (char*) "unbind";
		break;
	case BOTH_UBD_RESP:						//3.3		3.4			5.0
		this->command_id_string = (char*) "unbind_resp";
		break;
	case ESME_BND_RECEIVER: 				//3.3		3.4			5.0
		this->command_id_string = (char*) "bind_receiver";
		break;
	case ESME_BND_RECEIVER_RESP: 			//3.3		3.4			5.0
		this->command_id_string = (char*) "bind_receiver_resp";
		break;
	case ESME_BND_TRANSMITTER:				//3.3		3.4			5.0
		this->command_id_string = (char*) "bind_transmitter";
		break;
	case ESME_BND_TRANSMITTER_RESP:			//3.3		3.4			5.0
		this->command_id_string = (char*) "bind_transmitter_resp";
		break;
	case ESME_BND_TRANSCEIVER:				//			3.4			5.0
		this->command_id_string = (char*) "bind_transceiver";
		break;
	case ESME_BND_TRANSCEIVER_RESP:			//			3.4			5.0
		this->command_id_string = (char*) "bind_transceiver_resp";
		break;
	case BOTH_QRYLINK:						//3.3		3.4			5.0
		this->command_id_string = (char*) "enquire_link";
		break;
	case BOTH_QRYLINK_RESP:					//3.3		3.4			5.0
		this->command_id_string = (char*) "enquire_link_resp";
		break;
	case ESME_DATA_SM:						//3.3		3.4			5.0
		this->command_id_string = (char*) "data_sm";
		break;
	case ESME_DATA_SM_RESP:					//3.3		3.4			5.0
		this->command_id_string = (char*) "data_sm_resp";
		break;
	case ESME_QUERY_SM:						//3.3		3.4			5.0
		this->command_id_string = (char*) "query_sm";
		break;
	case ESME_QUERY_SM_RESP:				//3.3		3.4			5.0
		this->command_id_string = (char*) "query_sm_resp";
		break;
	case ESME_SUBMIT_MULTI:					//3.3		3.4			5.0
		this->command_id_string = (char*) "submit_multi";
		break;
	case ESME_SUBMIT_MULTI_RESP:			//3.3		3.4			5.0
		this->command_id_string = (char*) "submit_multi_resp";
		break;
	case BOTH_GENERIC_NACK: 				//3.3		3.4			5.0
		this->command_id_string = (char*) "generic_nack";
		break;
	case ESME_REPLACE_SM:					//3.3		3.4			5.0
		this->command_id_string = (char*) "replace_sm";
		break;
	case ESME_REPLACE_SM_RESP:				//3.3		3.4			5.0
		this->command_id_string = (char*) "replace_sm_resp";
		break;
	case ESME_CANCEL_SM:					//3.3		3.4			5.0
		this->command_id_string = (char*) "cancel_sm";
		break;
	case ESME_CANCEL_SM_RESP:				//3.3		3.4			5.0
		this->command_id_string = (char*) "cancel_sm_resp";
		break;
	case SMSC_ALERT_NOT:					//3.3		3.4			5.0
		this->command_id_string = (char*) "alert_notification";
		break;
	case SMSC_OUTBD:						//			3.4			5.0
		this->command_id_string = (char*) "outbind";
		break;
	case ESME_PARAM_RETRIEVE:				//3.3
		this->command_id_string = (char*) "param_retrieve";
		break;
	case ESME_PARAM_RETRIEVE_RESP:			//3.3
		this->command_id_string = (char*) "param_retrieve_resp";
		break;
	case ESME_QUERY_LAST_MSGS:				//3.3
		this->command_id_string = (char*) "query_last_msgs";
		break;
	case ESME_QUERY_LAST_MSGS_RESP:			//3.3
		this->command_id_string = (char*) "query_last_msgs_resp";
		break;
	case ESME_QUERY_MSG_DETAILS:			//3.3
		this->command_id_string = (char*) "query_msg_details";
		break;
	case ESME_QUERY_MSG_DETAILS_RESP:		//3.3
		this->command_id_string = (char*) "query_msg_details_resp";
		break;
	case ESME_BCAST_SM:						//						5.0
		this->command_id_string = (char*) "broadcast_sm";
		break;
	case ESME_BCAST_SM_RESP:				//						5.0
		this->command_id_string = (char*) "broadcast_sm_resp";
		break;
	case ESME_QUERY_BCAST_SM:				//						5.0
		this->command_id_string = (char*) "query_broadcast_sm";
		break;
	case ESME_QUERY_BCAST_SM_RESP:			//						5.0
		this->command_id_string = (char*) "query_broadcast_sm_resp";
		break;
	case ESME_CANCEL_BCAST_SM:				//						5.0
		this->command_id_string = (char*) "cancel_broadcast_sm";
		break;
	case ESME_CANCEL_BCAST_SM_RESP:			//						5.0
		this->command_id_string = (char*) "cancel_broadcast_sm_resp";
		break;
	default:
		this->command_id_string = (char*) "unknown or reserved";
		break;
	}
}

void CommandId::setFullCommandIdString() {
	switch (this->myUnsignedInteger)
	{
	case ESME_SUBMIT_SM:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "Submit a short-message";
		break;
	case ESME_SUBMIT_SM_RESP:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case SMSC_DELIVER_SM:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case SMSC_DELIVER_SM_RESP:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case BOTH_UBD:							//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case BOTH_UBD_RESP:						//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_RECEIVER: 				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_RECEIVER_RESP: 			//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_TRANSMITTER:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_TRANSMITTER_RESP:			//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_TRANSCEIVER:				//			3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BND_TRANSCEIVER_RESP:			//			3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case BOTH_QRYLINK:						//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case BOTH_QRYLINK_RESP:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_DATA_SM:						//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_DATA_SM_RESP:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_SM:						//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_SM_RESP:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_SUBMIT_MULTI:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_SUBMIT_MULTI_RESP:			//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case BOTH_GENERIC_NACK: 				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_REPLACE_SM:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_REPLACE_SM_RESP:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_CANCEL_SM:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_CANCEL_SM_RESP:				//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case SMSC_ALERT_NOT:					//3.3		3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case SMSC_OUTBD:						//			3.4			5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_PARAM_RETRIEVE:				//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_PARAM_RETRIEVE_RESP:			//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_LAST_MSGS:				//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_LAST_MSGS_RESP:			//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_MSG_DETAILS:			//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_MSG_DETAILS_RESP:		//3.3
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BCAST_SM:						//						5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_BCAST_SM_RESP:				//						5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_BCAST_SM:				//						5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_QUERY_BCAST_SM_RESP:			//						5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_CANCEL_BCAST_SM:				//						5.0
		this->full_command_id_string = (char*) "";
		break;
	case ESME_CANCEL_BCAST_SM_RESP:			//						5.0
		this->full_command_id_string = (char*) "";
		break;
	default:
		this->full_command_id_string = (char*) "Unknown message or Reserved message";
		break;
	}
}
