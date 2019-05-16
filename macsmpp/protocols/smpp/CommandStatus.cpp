/*
 * CommandStatus.cpp
 *
 *  Created on: 07/11/2011
 *      Author: Bob Kerr
 */

#include "CommandStatus.h"

CommandStatus::CommandStatus() {
#ifdef DEBUG
	cout << "CommandStatus::CommandStatus()" << endl;
#endif
	this->error_string = NULL;
	this->full_error_string = NULL;
}

CommandStatus::~CommandStatus() {
#ifdef DEBUG
	cout << "CommandStatus::~CommandStatus()" << endl;
#endif
	this->error_string = NULL;
	this->full_error_string = NULL;
}

ostream& operator<< (ostream& myOStream, CommandStatus& cCmdStat) {
	myOStream << "command_status = 0x" << internal << setw(8) << setfill('0') << hex << cCmdStat.myUnsignedInteger << " (" << cCmdStat.getErrorString() << ")";

	return myOStream;
}

char* CommandStatus::getErrorString() {
	if (error_string == NULL) setErrorString();
	return error_string;
}

char* CommandStatus::getFullErrorString() {
	if (full_error_string == NULL) getFullErrorString();
	return full_error_string;
}

void CommandStatus::setErrorString() {
	switch (this->myUnsignedInteger)
	{
		case ESME_ROK:
			this->error_string = (char*) "ESME_ROK";
			break;
		case ESME_RINVMSGLEN:
			this->error_string = (char*) "ESME_RINVMSGLEN";
			break;
		case ESME_RINVCMDLEN:
			this->error_string = (char*) "ESME_RINVCMDLEN";
			break;
		case ESME_RINVCMDID:
			this->error_string = (char*) "ESME_RINVCMDID";
			break;
		case ESME_RINVBNDSTS:
			this->error_string = (char*) "ESME_RINVBNDSTS";
			break;
		case ESME_RALYBND:
			this->error_string = (char*) "ESME_RALYBND";
			break;
		case ESME_RINVPRTFLG:
			this->error_string = (char*) "ESME_RINVPRTFLG";
			break;
		case ESME_RINVREGDLVFLG:
			this->error_string = (char*) "ESME_RINVREGDLVFLG";
			break;
		case ESME_RSYSERR:
			this->error_string = (char*) "ESME_RSYSERR";
			break;
		case ESME_RINVSRCADR:
			this->error_string = (char*) "ESME_RINVSRCADR";
			break;
		case ESME_RINVDSTADR:
			this->error_string = (char*) "ESME_RINVDSTADR";
			break;
		case ESME_RINVMSGID:
			this->error_string = (char*) "ESME_RINVMSGID";
			break;
		case ESME_RBINDFAIL:
			this->error_string = (char*) "ESME_RBINDFAIL";
			break;
		case ESME_RINVPASWD:
			this->error_string = (char*) "ESME_RINVPASWD";
			break;
		case ESME_RINVSYSID:
			this->error_string = (char*) "ESME_RINVSYSID";
			break;
		case ESME_RCANCELFAIL:
			this->error_string = (char*) "ESME_RCANCELFAIL";
			break;
		case ESME_RREPLACEFAIL:
			this->error_string = (char*) "ESME_RREPLACEFAIL";
			break;
		case ESME_RMSGQFUL:
			this->error_string = (char*) "ESME_RMSGQFUL";
			break;
		case ESME_RINVSERTYP:
			this->error_string = (char*) "ESME_RINVSERTYP";
			break;
		case ESME_RINVNUMDESTS:
			this->error_string = (char*) "ESME_RINVNUMDESTS";
			break;
		case ESME_RINVDLNAME:
			this->error_string = (char*) "ESME_RINVDLNAME";
			break;
		case ESME_RINVDESTFLAG:
			this->error_string = (char*) "ESME_RINVDESTFLAG";
			break;
		case ESME_RINVSUBREP:
			this->error_string = (char*) "ESME_RINVSUBREP";
			break;
		case ESME_RINVESMCLASS:
			this->error_string = (char*) "ESME_RINVESMCLASS";
			break;
		case ESME_RCNTSUBDL:
			this->error_string = (char*) "ESME_RCNTSUBDL";
			break;
		case ESME_RSUBMITFAIL:
			this->error_string = (char*) "ESME_RSUBMITFAIL";
			break;
		case ESME_RINVSRCTON:
			this->error_string = (char*) "ESME_RINVSRCTON";
			break;
		case ESME_RINVSRCNPI:
			this->error_string = (char*) "ESME_RINVSRCNPI";
			break;
		case ESME_RINVDSTTON:
			this->error_string = (char*) "ESME_RINVDSTTON";
			break;
		case ESME_RINVDSTNPI:
			this->error_string = (char*) "ESME_RINVDSTNPI";
			break;
		case ESME_RINVSYSTYP:
			this->error_string = (char*) "ESME_RINVSYSTYP";
			break;
		case ESME_RINVREPFLAG:
			this->error_string = (char*) "ESME_RINVREPFLAG";
			break;
		case ESME_RINVNUMMSGS:
			this->error_string = (char*) "ESME_RINVNUMMSGS";
			break;
		case ESME_RTHROTTLED:
			this->error_string = (char*) "ESME_RTHROTTLED";
			break;
		case ESME_RINVSCHED:
			this->error_string = (char*) "ESME_RINVSCHED";
			break;
		case ESME_RINVEXPIRY:
			this->error_string = (char*) "ESME_RINVEXPIRY";
			break;
		case ESME_RINVDFTMSGID:
			this->error_string = (char*) "ESME_RINVDFTMSGID";
			break;
		case ESME_RX_T_APPN:
			this->error_string = (char*) "ESME_RX_T_APPN";
			break;
		case ESME_RX_P_APPN:
			this->error_string = (char*) "ESME_RX_P_APPN";
			break;
		case ESME_RX_R_APPN:
			this->error_string = (char*) "ESME_RX_R_APPN";
			break;
		case ESME_RQUERYFAIL:
			this->error_string = (char*) "ESME_RQUERYFAIL";
			break;
		case ESME_RINVOPTPARSTREAM:
			this->error_string = (char*) "ESME_RINVOPTPARSTREAM";
			break;
		case ESME_ROPTPARNOTALLWD:
			this->error_string = (char*) "ESME_ROPTPARNOTALLWD";
			break;
		case ESME_RINVPARLEN:
			this->error_string = (char*) "ESME_RINVPARLEN";
			break;
		case ESME_RMISSINGOPTPARAM:
			this->error_string = (char*) "ESME_RMISSINGOPTPARAM";
			break;
		case ESME_RINVOPTPARAMVAL:
			this->error_string = (char*) "ESME_RINVOPTPARAMVAL";
			break;
		case ESME_RDELIVERYFAILURE:
			this->error_string = (char*) "ESME_RDELIVERYFAILURE";
			break;
		case ESME_RUNKNOWNERR:
			this->error_string = (char*) "ESME_RUNKNOWNERR";
			break;
		default:
			this->error_string = (char*) "Unknown Error or reserved error";
			break;
	}
}

void CommandStatus::setFullErrorString() {
	switch (this->myUnsignedInteger)
	{
		case ESME_ROK:
			this->full_error_string = (char*) "No Error";
			break;
		case ESME_RINVMSGLEN:
			this->full_error_string = (char*) "Message Length is invalid";
			break;
		case ESME_RINVCMDLEN:
			this->full_error_string = (char*) "Command Length is invalid";
			break;
		case ESME_RINVCMDID:
			this->full_error_string = (char*) "Invalid Command ID";
			break;
		case ESME_RINVBNDSTS:
			this->full_error_string = (char*) "Incorrect BIND Status for given command";
			break;
		case ESME_RALYBND:
			this->full_error_string = (char*) "ESME Already in Bound State";
			break;
		case ESME_RINVPRTFLG:
			this->full_error_string = (char*) "Invalid Priority Flag";
			break;
		case ESME_RINVREGDLVFLG:
			this->full_error_string = (char*) "Invalid Registered Delivery Flag";
			break;
		case ESME_RSYSERR:
			this->full_error_string = (char*) "System Error";
			break;
		case ESME_RINVSRCADR:
			this->full_error_string = (char*) "Invalid Source Address";
			break;
		case ESME_RINVDSTADR:
			this->full_error_string = (char*) "Invalid Destination Address";
			break;
		case ESME_RINVMSGID:
			this->full_error_string = (char*) "Message ID is invalid";
			break;
		case ESME_RBINDFAIL:
			this->full_error_string = (char*) "Bind Failed";
			break;
		case ESME_RINVPASWD:
			this->full_error_string = (char*) "Invalid Password";
			break;
		case ESME_RINVSYSID:
			this->full_error_string = (char*) "Invalid System ID";
			break;
		case ESME_RCANCELFAIL:
			this->full_error_string = (char*) "Cancel SM Failed";
			break;
		case ESME_RREPLACEFAIL:
			this->full_error_string = (char*) "Replace SM Failed";
			break;
		case ESME_RMSGQFUL:
			this->full_error_string = (char*) "Message Queue Full";
			break;
		case ESME_RINVSERTYP:
			this->full_error_string = (char*) "Invalid Service Type";
			break;
		case ESME_RINVNUMDESTS:
			this->full_error_string = (char*) "Invalid number of destinations";
			break;
		case ESME_RINVDLNAME:
			this->full_error_string = (char*) "Invalid Distribution List name";
			break;
		case ESME_RINVDESTFLAG:
			this->full_error_string = (char*) "Destination flag is invalid (submit_multi)";
			break;
		case ESME_RINVSUBREP:
			this->full_error_string = (char*) "Invalid 'submit with replace' request (i.e. submit_sm with replace_if_present_flag set)";
			break;
		case ESME_RINVESMCLASS:
			this->full_error_string = (char*) "Invalid esm_class field data";
			break;
		case ESME_RCNTSUBDL:
			this->full_error_string = (char*) "Cannot Submit to Distribution List";
			break;
		case ESME_RSUBMITFAIL:
			this->full_error_string = (char*) "submit_sm or submit_multi failed";
			break;
		case ESME_RINVSRCTON:
			this->full_error_string = (char*) "Invalid Source address TON";
			break;
		case ESME_RINVSRCNPI:
			this->full_error_string = (char*) "Invalid Source address NPI";
			break;
		case ESME_RINVDSTTON:
			this->full_error_string = (char*) "Invalid Destination address TON";
			break;
		case ESME_RINVDSTNPI:
			this->full_error_string = (char*) "Invalid Destination address NPI";
			break;
		case ESME_RINVSYSTYP:
			this->full_error_string = (char*) "Invalid system_type field";
			break;
		case ESME_RINVREPFLAG:
			this->full_error_string = (char*) "Invalid replace_if_present flag";
			break;
		case ESME_RINVNUMMSGS:
			this->full_error_string = (char*) "Invalid number of messages";
			break;
		case ESME_RTHROTTLED:
			this->full_error_string = (char*) "Throttling error (ESME has exceeded allowed message limits)";
			break;
		case ESME_RINVSCHED:
			this->full_error_string = (char*) "Invalid Scheduled Delivery Time";
			break;
		case ESME_RINVEXPIRY:
			this->full_error_string = (char*) "Invalid message validity period (Expiry time)";
			break;
		case ESME_RINVDFTMSGID:
			this->full_error_string = (char*) "Predefined Message Invalid or Not Found";
			break;
		case ESME_RX_T_APPN:
			this->full_error_string = (char*) "ESME Receiver Temporary App Error Code";
			break;
		case ESME_RX_P_APPN:
			this->full_error_string = (char*) "ESME Receiver Permanent App Error Code";
			break;
		case ESME_RX_R_APPN:
			this->full_error_string = (char*) "ESME Receiver Reject Message Error Code";
			break;
		case ESME_RQUERYFAIL:
			this->full_error_string = (char*) "query_sm request failed";
			break;
		case ESME_RINVOPTPARSTREAM:
			this->full_error_string = (char*) "Error in the optional part of the PDU Body.";
			break;
		case ESME_ROPTPARNOTALLWD:
			this->full_error_string = (char*) "Optional Parameter not allowed";
			break;
		case ESME_RINVPARLEN:
			this->full_error_string = (char*) "Invalid Parameter Length.";
			break;
		case ESME_RMISSINGOPTPARAM:
			this->full_error_string = (char*) "Expected Optional Parameter missing";
			break;
		case ESME_RINVOPTPARAMVAL:
			this->full_error_string = (char*) "Invalid Optional Parameter Value";
			break;
		case ESME_RDELIVERYFAILURE:
			this->full_error_string = (char*) "Delivery Failure (used for data_sm_resp)";
			break;
		case ESME_RUNKNOWNERR:
			this->full_error_string = (char*) "Unknown Error";
			break;
		default:
			this->full_error_string = (char*) "Unknown Error or reserved error";
			break;
	}
}


