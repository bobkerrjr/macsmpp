/*
 * CommandId.h
 *
 *  Created on: 07/11/2011
 *      Author: Bob Kerr
 */

#ifndef COMMANDID_H_
#define COMMANDID_H_
#include "../../types/UnsignedInteger.h"

#define BOTH_GENERIC_NACK				0x80000000 //3.3		3.4			5.0
#define ESME_BND_RECEIVER				0x00000001 //3.3		3.4			5.0
#define ESME_BND_RECEIVER_RESP			0x80000001 //3.3		3.4			5.0
#define ESME_BND_TRANSMITTER			0x00000002 //3.3		3.4			5.0
#define ESME_BND_TRANSMITTER_RESP		0x80000002 //3.3		3.4			5.0
#define ESME_QUERY_SM					0x00000003 //3.3		3.4			5.0
#define ESME_QUERY_SM_RESP				0x80000003 //3.3		3.4			5.0
#define ESME_SUBMIT_SM					0x00000004 //3.3		3.4			5.0
#define ESME_SUBMIT_SM_RESP				0x80000004 //3.3		3.4			5.0
#define SMSC_DELIVER_SM					0x00000005 //3.3		3.4			5.0
#define SMSC_DELIVER_SM_RESP			0x80000005 //3.3		3.4			5.0
#define BOTH_UBD						0x00000006 //3.3		3.4			5.0
#define BOTH_UBD_RESP					0x80000006 //3.3		3.4			5.0
#define ESME_REPLACE_SM					0x00000007 //3.3		3.4			5.0
#define ESME_REPLACE_SM_RESP			0x80000007 //3.3		3.4			5.0
#define ESME_CANCEL_SM					0x00000008 //3.3		3.4			5.0
#define ESME_CANCEL_SM_RESP				0x80000008 //3.3		3.4			5.0
#define ESME_BND_TRANSCEIVER			0x00000009 //			3.4			5.0
#define ESME_BND_TRANSCEIVER_RESP		0x80000009 //			3.4			5.0
#define SMSC_OUTBD						0x0000000B //			3.4			5.0
#define BOTH_QRYLINK					0x00000015 //3.3		3.4			5.0
#define BOTH_QRYLINK_RESP				0x80000015 //3.3		3.4			5.0
#define ESME_SUBMIT_MULTI				0x00000021 //3.3		3.4			5.0
#define ESME_SUBMIT_MULTI_RESP			0x80000021 //3.3		3.4			5.0
#define ESME_PARAM_RETRIEVE 			0x00000022 //3.3
#define ESME_PARAM_RETRIEVE_RESP		0x80000022 //3.3
#define ESME_QUERY_LAST_MSGS 			0x00000023 //3.3
#define ESME_QUERY_LAST_MSGS_RESP 		0x80000023 //3.3
#define ESME_QUERY_MSG_DETAILS 			0x00000024 //3.3
#define ESME_QUERY_MSG_DETAILS_RESP		0x80000024 //3.3
#define SMSC_ALERT_NOT					0x00000102 //			3.4			5.0
#define ESME_DATA_SM					0x00000103 //			3.4			5.0
#define ESME_DATA_SM_RESP				0x80000103 //			3.4			5.0
#define ESME_BCAST_SM					0x00000111 //						5.0
#define ESME_BCAST_SM_RESP				0x80000111 //						5.0
#define ESME_QUERY_BCAST_SM				0x00000112 //						5.0
#define ESME_QUERY_BCAST_SM_RESP		0x80000112 //						5.0
#define ESME_CANCEL_BCAST_SM			0x00000113 //						5.0
#define ESME_CANCEL_BCAST_SM_RESP		0x80000113 //						5.0


/*
 *	PARAM_RETRIEVE 				= 0x00000022; //3.3
 *	PARAM_RETRIEVE_RESP 		= 0x80000022; //3.3
 *	QUERY_LAST_MSGS 			= 0x00000023; //3.3
 *	QUERY_LAST_MSGS_RESP 		= 0x80000023; //3.3
 *	QUERY_MSG_DETAILS 			= 0x00000024; //3.3
 *	QUERY_MSG_DETAILS_RESP 		= 0x80000024; //3.3
 *
 *	broadcast_sm  				= 0x00000111; //5.0
 *	query_broadcast_sm 			= 0x00000112; //5.0
 *	cancel_broadcast_sm 		= 0x00000113; //5.0
 *	broadcast_sm_resp  			= 0x80000111; //5.0
 *	query_broadcast_sm_resp  	= 0x80000112; //5.0
 *	cancel_broadcast_sm_resp  	= 0x80000113; //5.0
 *
 *  ESME_BNDRCV									bind_receiver								Bind to SMSC Kernel as a receiver
 *  ESME_BNDRCV_RESP							bind_receiver_resp							Response to bind_receiver
 *  ESME_BNDTRN									bind_transmitter							Bind to SMSC Kernel as transmitter
 *  ESME_BNDTRN_RESP							bind_transmitrer_resp						Response to bind_transmitter
 *  ESME_UBD									unbind										Unbind from SMSC Kernel
 *  ESME_UBD_RESP								unbind_resp									Response to unbind
 *  ESME_SUB_SM									submit_sm									Submit a short-message
 *  ESME_SUB_SM_RESP							submit_sm_resp								Response to submit_sm
 *  ESME_SUB_MULTI								submit_multi								Submit a short message to an SME Address
 *  ESME_SUB_MULTI_RESP							submit_multi_resp							Respose to submit_multi.
 *  SMSC_DELIVER_SM								deliver_sm									Submit a short-message to ESME
 *  SMSC_DELIVER_SM_RESP						deliver_sm_resp								Response to deliver_sm
 *  ESME_QUERY_SM								query_sm									Query status of a short-message
 *  ESME_QUERY_SM_RESP							query_sm_resp								Response to query_sm
 *  ESME_QUERY_LAST_MSGS						query_last_msgs								Query status of a certain number of messages in the database with a specific source address.
 *  ESME_QUERY_LAST_MSGS_RESP					query_last_msgs_resp						Response to query_last_msgs.
 *  ESME_QUERY_MSG_DETAILS						query_msg_details							Query the details of a particular message.
 *  ESME_QUERY_MSG_DETAILS_RESP					query_msg_details_resp						Response to query_msg_details.
 *  ESME_CANCEL_SM								cancel_sm									Cancel a short message(s)
 *  ESME_CANCEL_SM_RESP							cancel_sm_resp								Response to cancel_sm
 *  ESME_REPLACE_SM								replace_sm									Replace a short message
 *  ESME_REPLACE_SM_RESP						replace_sm_resp								Response to replace_sm
 *  ESME_QRYLINK								enquire_link								Link confidence check
 *  ESME_QRYLINK_RESP							enquire_link_resp							Response to enquire_link
 *  ESME_PARAM_RETRIEVE							param_retrieve								Retrieve value for configurable parameter
 *  ESME_PARAM_RETRIEVE_RESP					param_retrieve_resp							Response to param_retrieve
 *  ESME_NACK									generic_nack								Negative Acknowledgement
 */


/*
	switch(header->getCommandId())
	{
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
	case ESME_BND_TRANSCEIVER:				//			3.4			5.0
	case ESME_BND_TRANSCEIVER_RESP:			//			3.4			5.0
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
	case SMSC_OUTBD:						//			3.4			5.0
	case ESME_PARAM_RETRIEVE:				//3.3
	case ESME_PARAM_RETRIEVE_RESP:			//3.3
	case ESME_QUERY_LAST_MSGS:				//3.3
	case ESME_QUERY_LAST_MSGS_RESP:			//3.3
	case ESME_QUERY_MSG_DETAILS:			//3.3
	case ESME_QUERY_MSG_DETAILS_RESP:		//3.3
	case ESME_BCAST_SM:						//						5.0
	case ESME_BCAST_SM_RESP:				//						5.0
	case ESME_QUERY_BCAST_SM:				//						5.0
	case ESME_QUERY_BCAST_SM_RESP:			//						5.0
	case ESME_CANCEL_BCAST_SM:				//						5.0
	case ESME_CANCEL_BCAST_SM_RESP:			//						5.0
	default:
		break;
	}
 */


/* Reserved command IDs (info only)
Reserved								0x0000000A
Reserved								0x8000000A
Reserved								0x0000000C - 0x00000014
Reserved								0x8000000B - 0x80000014
Reserved								0x00000016-0x00000020
Reserved								0x80000016-0x80000020
Reserved								0x00000022-0x000000FF
Reserved								0x80000022-0x800000FF
Reserved								0x00000100
Reserved								0x80000100
Reserved								0x00000101
Reserved								0x80000101
Reserved								0x80000102
Reserved for SMPP extension				0x00000104-0x0000FFFF
Reserved for SMPP extension				0x80000104-0x8000FFFF
Reserved								0x00010000-0x000101FF
Reserved								0x80010000-0x800101FF
Reserved for SMSC Vendor				0x00010200-0x000102FF
Reserved for SMSC Vendor				0x80010200-0x800102FF
Reserved								0x00010300-0xFFFFFFFF
*/

class CommandId : public UnsignedInteger {
public:
	CommandId();
	~CommandId();
    char* getCommandIdString();
    char* getFullCommandIdString();
    void setCommandIdString();
    void setFullCommandIdString();
    friend ostream& operator<< (ostream& myOStream, CommandId& cCmdId);
protected:
	char*								command_id_string;
	char*								full_command_id_string;
};

#endif /* COMMANDID_H_ */
