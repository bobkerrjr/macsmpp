/*
 * CommandStatus.h
 *
 *  Created on: 07/11/2011
 *      Author: Bob Kerr
 */

#ifndef COMMANDSTATUS_H_
#define COMMANDSTATUS_H_
#include "../../types/UnsignedInteger.h"

#define ESME_ROK 									0x00000000 //No Error
#define ESME_RINVMSGLEN 							0x00000001 //Message Length is invalid
#define ESME_RINVCMDLEN 							0x00000002 //Command Length is invalid
#define ESME_RINVCMDID 								0x00000003 //Invalid Command ID
#define ESME_RINVBNDSTS 							0x00000004 //Incorrect BIND Status for given command
#define ESME_RALYBND 								0x00000005 //ESME Already in Bound State
#define ESME_RINVPRTFLG 							0x00000006 //Invalid Priority Flag
#define ESME_RINVREGDLVFLG 							0x00000007 //Invalid Registered Delivery Flag
#define ESME_RSYSERR 								0x00000008 //System Error
#define ESME_RINVSRCADR 							0x0000000A //Invalid Source Address
#define ESME_RINVDSTADR 							0x0000000B //Invalid Dest Addr
#define ESME_RINVMSGID 								0x0000000C //Message ID is invalid
#define ESME_RBINDFAIL 								0x0000000D //Bind Failed
#define ESME_RINVPASWD 								0x0000000E //Invalid Password
#define ESME_RINVSYSID 								0x0000000F //Invalid System ID
#define ESME_RCANCELFAIL 							0x00000011 //Cancel SM Failed
#define ESME_RREPLACEFAIL 							0x00000013 //Replace SM Failed
#define ESME_RMSGQFUL 								0x00000014 //Message Queue Full
#define ESME_RINVSERTYP								0x00000015 //Invalid Service Type
#define ESME_RINVNUMDESTS 							0x00000033 //Invalid number of destinations
#define ESME_RINVDLNAME 							0x00000034 //Invalid Distribution List name
#define ESME_RINVDESTFLAG 							0x00000040 //Destination flag is invalid (submit_multi)
#define ESME_RINVSUBREP 							0x00000042 //Invalid ‘submit with replace’ request (i.e. submit_sm with replace_if_present_flag set)
#define ESME_RINVESMCLASS 							0x00000043 //Invalid esm_class field data
#define ESME_RCNTSUBDL 								0x00000044 //Cannot Submit to Distribution List
#define ESME_RSUBMITFAIL 							0x00000045 //submit_sm or submit_multi failed
#define ESME_RINVSRCTON 							0x00000048 //Invalid Source address TON
#define ESME_RINVSRCNPI 							0x00000049 //Invalid Source address NPI
#define ESME_RINVDSTTON 							0x00000050 //Invalid Destination address TON
#define ESME_RINVDSTNPI 							0x00000051 //Invalid Destination address NPI
#define ESME_RINVSYSTYP 							0x00000053 //Invalid system_type field
#define ESME_RINVREPFLAG 							0x00000054 //Invalid replace_if_present flag
#define ESME_RINVNUMMSGS 							0x00000055 //Invalid number of messages
#define ESME_RTHROTTLED 							0x00000058 //Throttling error (ESME has exceeded allowed message limits)
#define ESME_RINVSCHED 								0x00000061 //Invalid Scheduled Delivery Time
#define ESME_RINVEXPIRY 							0x00000062 //Invalid message validity period (Expiry time)
#define ESME_RINVDFTMSGID 							0x00000063 //Predefined Message Invalid or Not Found
#define ESME_RX_T_APPN 								0x00000064 //ESME Receiver Temporary App Error Code
#define ESME_RX_P_APPN 								0x00000065 //ESME Receiver Permanent App Error Code
#define ESME_RX_R_APPN 								0x00000066 //ESME Receiver Reject Message Error Code
#define ESME_RQUERYFAIL 							0x00000067 //query_sm request failed
#define ESME_RINVOPTPARSTREAM 						0x000000C0 //Error in the optional part of the PDU Body.
#define ESME_ROPTPARNOTALLWD 						0x000000C1 //Optional Parameter not allowed
#define ESME_RINVPARLEN 							0x000000C2 //Invalid Parameter Length.
#define ESME_RMISSINGOPTPARAM 						0x000000C3 //Expected Optional Parameter missing
#define ESME_RINVOPTPARAMVAL 						0x000000C4 //Invalid Optional Parameter Value
#define ESME_RDELIVERYFAILURE 						0x000000FE //Delivery Failure (used for data_sm_resp)
#define ESME_RUNKNOWNERR 							0x000000FF //Unknown Error

/* Reserved command_status
Reserved 0x00000009
Reserved 0x00000010
Reserved 0x00000012
Reserved 0x00000016-0x00000032
Reserved 0x00000035-0x0000003F
Reserved 0x00000041
Reserved 0x00000046-0x00000047
Reserved 0x00000052
Reserved 0x00000056-0x00000057
Reserved 0x00000059-0x00000060
Reserved 0x00000068-0x000000BF
Reserved 0x000000C5-0x000000FD
Reserved for SMPP extension 0x00000100-0x000003FF
Reserved for SMSC vendor specific errors 0x00000400-0x000004FF
Reserved 0x00000500-0xFFFFFFFF
*/

class CommandStatus : public UnsignedInteger {
public:
	CommandStatus();
	~CommandStatus();
    char* getErrorString();
    char* getFullErrorString();
    void setErrorString();
    void setFullErrorString();
    friend ostream& operator<< (ostream& myOStream, CommandStatus& cCmdStat);
protected:
	char*								error_string;
	char*								full_error_string;
};

#endif /* COMMANDSTATUS_H_ */
