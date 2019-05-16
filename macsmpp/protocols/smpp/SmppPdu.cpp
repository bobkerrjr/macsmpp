/*
 * SmppPdu.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: Bob Kerr
 */

#include "SmppPdu.h"
#include "CommandStatus.h"
#include "CommandId.h"
#include "SubmitSm.h"
#include "SubmitSmResp.h"
#include "SubmitMulti.h"
#include "SubmitMultiResp.h"
#include "DeliverSm.h"
#include "DeliverSmResp.h"
#include "AlertNotification.h"
#include "CancelSm.h"
#include "ReplaceSm.h"
#include "QuerySm.h"
#include "QuerySmResp.h"
#include "DataSm.h"
#include "DataSmResp.h"
#include "Outbind.h"
#include "BindReceiver.h"
#include "BindReceiverResp.h"
#include "BindTransmitter.h"
#include "BindTransmitterResp.h"
#include "BindTransceiver.h"
#include "BindTransceiverResp.h"
#include "ParamRetrieve.h"
#include "ParamRetrieveResp.h"
#include "QueryLastMsgs.h"
#include "QueryLastMsgsResp.h"
#include "QueryMsgDetails.h"
#include "QueryMsgDetailsResp.h"
#include "BroadcastSm.h"
#include "BroadcastSmResp.h"
#include "QueryBroadcastSm.h"
#include "QueryBroadcastSmResp.h"
#include "CancelBroadcastSm.h"
#include <iostream>
#include <iomanip>
using namespace std;

SmppPdu::SmppPdu() {
#ifdef DEBUG
	cout << "SmppPdu::SmppPdu()" << endl;
#endif
	this->init();
}

SmppPdu::SmppPdu(char * buffer) {
#ifdef DEBUG
		cout << "SmppPdu::SmppPdu(char* buffer)" << endl;
#endif
	this->init();
	this->pduDecode(buffer);
}

SmppPdu::~SmppPdu() {
#ifdef DEBUG
	cout << "SmppPdu::~SmppPdu()" << endl;
#endif
	this->destroy();
}

void SmppPdu::init() {
	this->body = NULL;
	this->header = NULL;
	this->isValid = true;
}

void SmppPdu::destroy() {
	if (header != NULL)
		delete header;
	if (body != NULL)
		delete body;
	this->init();
}

void SmppPdu::printPduInfo () {
	if (header != NULL) header->printPduInfo();
	if (body != NULL) body->printPduInfo();
}

void SmppPdu::pduDecode(char *buffer)
{
	this->destroy();

	//Decode PDU Header
	this->header = new SmppHeader(buffer);

	//Decode PDU Body
	if (this->header->getCommandLength() > (4 * sizeof (uint32_t))) {
		switch(header->getCommandId())
		{
			case ESME_SUBMIT_SM:					//3.3		3.4			5.0
			{
				SubmitSm *temp = new SubmitSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_SUBMIT_SM_RESP:				//3.3		3.4			5.0
			{
				SubmitSmResp *temp = new SubmitSmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case SMSC_DELIVER_SM:					//3.3		3.4			5.0
			{
				DeliverSm *temp = new DeliverSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case SMSC_DELIVER_SM_RESP:				//3.3		3.4			5.0
			{
				DeliverSmResp *temp = new DeliverSmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_RECEIVER: 				//3.3		3.4			5.0
			{
				BindReceiver *temp = new BindReceiver(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_RECEIVER_RESP: 			//3.3		3.4			5.0
			{
				BindReceiverResp *temp = new BindReceiverResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_TRANSMITTER:				//3.3		3.4			5.0
			{
				BindTransmitter *temp = new BindTransmitter(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_TRANSMITTER_RESP:			//3.3		3.4			5.0
			{
				BindTransmitterResp *temp = new BindTransmitterResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_TRANSCEIVER:				//			3.4			5.0
			{
				BindTransceiver *temp = new BindTransceiver(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BND_TRANSCEIVER_RESP:			//			3.4			5.0
			{
				BindTransceiverResp *temp = new BindTransceiverResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_DATA_SM:						//3.3		3.4			5.0
			{
				DataSm *temp = new DataSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_DATA_SM_RESP:					//3.3		3.4			5.0
			{
				DataSmResp *temp = new DataSmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_SM:						//3.3		3.4			5.0
			{
				QuerySm *temp = new QuerySm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_SM_RESP:				//3.3		3.4			5.0
			{
				QuerySmResp *temp = new QuerySmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_SUBMIT_MULTI:					//3.3		3.4			5.0
			{
				SubmitMulti *temp = new SubmitMulti(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_SUBMIT_MULTI_RESP:			//3.3		3.4			5.0
			{
				SubmitMultiResp *temp = new SubmitMultiResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_REPLACE_SM:					//3.3		3.4			5.0
			{
				ReplaceSm *temp = new ReplaceSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_CANCEL_SM:					//3.3		3.4			5.0
			{
				CancelSm *temp = new CancelSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case SMSC_ALERT_NOT:					//3.3		3.4			5.0
			{
				AlertNotification *temp = new AlertNotification(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case SMSC_OUTBD:						//			3.4			5.0
			{
				Outbind *temp = new Outbind(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_PARAM_RETRIEVE:				//3.3
			{
				ParamRetrieve *temp = new ParamRetrieve(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_PARAM_RETRIEVE_RESP:			//3.3
			{
				ParamRetrieveResp *temp = new ParamRetrieveResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_LAST_MSGS:				//3.3
			{
				QueryLastMsgs *temp = new QueryLastMsgs(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_LAST_MSGS_RESP:			//3.3
			{
				QueryLastMsgsResp *temp = new QueryLastMsgsResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_MSG_DETAILS:			//3.3
			{
				QueryMsgDetails *temp = new QueryMsgDetails(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_MSG_DETAILS_RESP:		//3.3
			{
				QueryMsgDetailsResp *temp = new QueryMsgDetailsResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BCAST_SM:						//						5.0
			{
				BroadcastSm *temp = new BroadcastSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_BCAST_SM_RESP:				//						5.0
			{
				BroadcastSmResp *temp = new BroadcastSmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_BCAST_SM:				//						5.0
			{
				QueryBroadcastSm *temp = new QueryBroadcastSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_QUERY_BCAST_SM_RESP:			//						5.0
			{
				QueryBroadcastSmResp *temp = new QueryBroadcastSmResp(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}
			case ESME_CANCEL_BCAST_SM:				//						5.0
			{
				CancelBroadcastSm *temp = new CancelBroadcastSm(buffer,this->header->getCommandLength());
				this->body = dynamic_cast<SmppBody*>(temp);
				break;
			}

			//These PDUs don't use the body field
			case BOTH_QRYLINK:						//3.3		3.4			5.0
			case BOTH_QRYLINK_RESP:					//3.3		3.4			5.0
			case ESME_REPLACE_SM_RESP:				//3.3		3.4			5.0
			case ESME_CANCEL_SM_RESP:				//3.3		3.4			5.0
			case BOTH_GENERIC_NACK: 				//3.3		3.4			5.0
			case BOTH_UBD:							//3.3		3.4			5.0
			case BOTH_UBD_RESP:						//3.3		3.4			5.0
			case ESME_CANCEL_BCAST_SM_RESP:			//						5.0
				this->body = NULL;
				break;
			default:
				this->body = NULL;
				this->isValid = false;
				break;
		}
		/*
		if (this->body != NULL) {
			uint32_t errors = 0;
			errors = this->header->getCommandLength() - this->body->getNumOfByteErrors();
			this->header->setCommandLength(errors);
		}
		*/
	}
#ifdef DEBUG
	else {
	cout << "Skipped Body allocation." << endl;
	}
#endif
}

uint8_t* SmppPdu::pduEncode() {
	uint8_t* rValue = (uint8_t *) new uint8_t[this->header->getCommandLength()];
	this->header->pduEncode(rValue);

	return rValue;
}

bool SmppPdu::isVersion(uint8_t version) {
	bool rTemp = false;

	//Check if this PDU is equal to 'version'
	if (this->header != NULL)
		rTemp = this->header->isVersion(version);
	if (rTemp && (this->body != NULL))
		rTemp = this->body->isVersion(version);

	return rTemp;
}

bool SmppPdu::getIsValid() {
	bool bTemp = true;

	//Check if this PDU is valid or not
	if (this->body != NULL)
		bTemp = this->body->getIsValid();

	return (this->isValid && bTemp) ? true : false;
}
