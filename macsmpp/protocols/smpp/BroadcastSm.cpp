/*
 * BroadcastSm.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "BroadcastSm.h"
#include <iostream>
#include <iomanip>
using namespace std;

BroadcastSm::BroadcastSm() {
#ifdef DEBUG
	cout << "BroadcastSm::BroadcastSm()" << endl;
#endif
	this->init();
}

BroadcastSm::BroadcastSm(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "BroadcastSm::BroadcastSm(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

BroadcastSm::~BroadcastSm() {
#ifdef DEBUG
	cout << "BroadcastSm::~BroadcastSm()" << endl;
#endif
	this->destroy();
}

void BroadcastSm::destroy() {
	if (this->service_type != NULL) delete this->service_type;
	if (this->source_addr != NULL) delete this->source_addr;
	if (this->message_id != NULL) delete this->message_id;
	if (this->schedule_delivery_time != NULL) delete this->schedule_delivery_time;
	if (this->validity_period != NULL) delete this->validity_period;
	//TLV
	if (this->alert_on_msg_delivery != NULL) delete this->alert_on_msg_delivery;
	if (this->broadcast_area_identifier != NULL) delete this->broadcast_area_identifier;
	if (this->broadcast_channel_indicator != NULL) delete this->broadcast_channel_indicator;
	if (this->broadcast_content_type != NULL) delete this->broadcast_content_type;
	if (this->broadcast_content_type_info != NULL) delete this->broadcast_content_type_info;
	if (this->broadcast_frequency_interval != NULL) delete this->broadcast_frequency_interval;
	if (this->broadcast_message_class != NULL) delete this->broadcast_message_class;
	if (this->broadcast_rep_num != NULL) delete this->broadcast_rep_num;
	if (this->broadcast_service_group != NULL) delete this->broadcast_service_group;
	if (this->callback_num != NULL) delete this->callback_num;
	if (this->callback_num_atag != NULL) delete this->callback_num_atag;
	if (this->callback_num_pres_ind != NULL) delete this->callback_num_pres_ind;
	if (this->dest_addr_subunit != NULL) delete this->dest_addr_subunit;
	if (this->dest_port != NULL) delete this->dest_port;
	if (this->dest_subaddress != NULL) delete this->dest_subaddress;
	if (this->display_time != NULL) delete this->display_time;
	if (this->language_indicator != NULL) delete this->language_indicator;
	if (this->message_payload != NULL) delete this->message_payload;
	if (this->ms_validity != NULL) delete this->ms_validity;
	if (this->payload_type != NULL) delete this->payload_type;
	if (this->privacy_indicator != NULL) delete this->privacy_indicator;
	if (this->sms_signal != NULL) delete this->sms_signal;
	if (this->source_addr_subunit != NULL) delete this->source_addr_subunit;
	if (this->source_port != NULL) delete this->source_port;
	if (this->source_subaddress != NULL) delete this->source_subaddress;
	if (this->user_message_reference != NULL) delete this->user_message_reference;
	this->init();
}

void BroadcastSm::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x04; // 5.0
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->service_type = NULL;
	this->source_addr = NULL;
	this->message_id = NULL;
	this->schedule_delivery_time = NULL;
	this->validity_period = NULL;
	//TLV
	this->alert_on_msg_delivery = NULL;
	this->broadcast_area_identifier = NULL;
	this->broadcast_channel_indicator = NULL;
	this->broadcast_content_type = NULL;
	this->broadcast_content_type_info = NULL;
	this->broadcast_frequency_interval = NULL;
	this->broadcast_message_class = NULL;
	this->broadcast_rep_num = NULL;
	this->broadcast_service_group = NULL;
	this->callback_num = NULL;
	this->callback_num_atag = NULL;
	this->callback_num_pres_ind = NULL;
	this->dest_addr_subunit = NULL;
	this->dest_port = NULL;
	this->dest_subaddress = NULL;
	this->display_time = NULL;
	this->language_indicator = NULL;
	this->message_payload = NULL;
	this->ms_validity = NULL;
	this->payload_type = NULL;
	this->privacy_indicator = NULL;
	this->sms_signal = NULL;
	this->source_addr_subunit = NULL;
	this->source_port = NULL;
	this->source_subaddress = NULL;
	this->user_message_reference = NULL;
}

void BroadcastSm::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	uint32_t x = 4 * sizeof (uint32_t); //size of header

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy service_type string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->service_type = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->service_type[i] = buffer[x+i];
	this->service_type[i] = 0;
	x+=++i;

	//Copy ton and npi values
	this->source_addr_ton.setMyUnsignedByte(buffer[x++]);
	this->source_addr_npi.setMyUnsignedByte((char) buffer[x++]);

	//Copy source_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->source_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->source_addr[i] = buffer[x+i];
	this->source_addr[i] = 0;
	x+=++i;

	//Copy message_id string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->message_id = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->message_id[i] = buffer[x+i];
	this->message_id[i] = 0;
	x+=++i;

	//Copy priority_flag value
	this->priority_flag = (char) buffer[x++];

	//Copy schedule_delivery_time string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->schedule_delivery_time = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->schedule_delivery_time[i] = buffer[x+i];
	this->schedule_delivery_time[i] = 0;
	x+=++i;

	//Copy validity_period string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->validity_period = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->validity_period[i] = buffer[x+i];
	this->validity_period[i] = 0;
	x+=++i;

	//Copy replace_if_present_flag, data_coding and sm_default_msg_id values
	this->replace_if_present_flag = (char) buffer[x++];
	this->data_coding = (char) buffer[x++];
	this->sm_default_msg_id = (char) buffer[x++];

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_BROADCAST_AREA_IDENTIFIER:
			this->broadcast_area_identifier = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_CONTENT_TYPE:
			this->broadcast_content_type = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_REP_NUM:
			this->broadcast_rep_num = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_FREQUENCY_INTERVAL:
			this->broadcast_frequency_interval = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_ALERT_ON_MESSAGE_DELIVERY:
			this->alert_on_msg_delivery = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_CHANNEL_INDICATOR:
			this->broadcast_channel_indicator = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_CONTENT_TYPE_INFO:
			this->broadcast_content_type_info = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_MESSAGE_CLASS:
			this->broadcast_message_class = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_BROADCAST_SERVICE_GROUP:
			this->broadcast_service_group = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_CALLBACK_NUM:
			this->callback_num = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_CALLBACK_NUM_ATAG:
			this->callback_num_atag = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_CALLBACK_NUM_PRES_IND:
			this->callback_num_pres_ind = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_DEST_ADDR_SUBUNIT:
			this->dest_addr_subunit = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_DEST_SUBADDRESS:
			this->dest_subaddress = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_DESTINATION_PORT:
			this->dest_port = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_DISPLAY_TIME:
			this->display_time = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_LANGUAGE_INDICATOR:
			this->language_indicator = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_MESSAGE_PAYLOAD:
			this->message_payload = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_MS_VALIDITY:
			this->ms_validity = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_PAYLOAD_TYPE:
			this->payload_type = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_PRIVACY_INDICATOR:
			this->privacy_indicator = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_SMS_SIGNAL:
			this->sms_signal = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_SOURCE_ADDR_SUBUNIT:
			this->source_addr_subunit = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_SOURCE_PORT:
			this->source_port = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_SOURCE_SUBADDRESS:
			this->source_subaddress = pTemp;
			x += pTemp->getBufSize();
			break;
		case TLV_USER_MESSAGE_REFERENCE:
			this->user_message_reference = pTemp;
			x += pTemp->getBufSize();
			break;
		default:
			x += pTemp->getBufSize();
			this->numOfByteErrors += pTemp->getBufSize();
#ifdef DEBUG
			cout << "Discarded pTemp->parameterTag = 0x" << internal << setw(4) << setfill('0') << hex << pTemp->getParameterTag() << " - " << pTemp->getTlvName() << endl;
#endif
			delete pTemp;
			this->isValid = false;
			//TODO: Treat error
			break;
		}
		pTemp = NULL;
	}

	if ((this->broadcast_area_identifier == NULL) ||
		(this->broadcast_content_type == NULL) ||
		(this->broadcast_rep_num == NULL) ||
		(this->broadcast_frequency_interval == NULL))
		this->isValid = false;

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void BroadcastSm::printPduInfo() {
	cout << "service_type = " << this->service_type << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			"message_id = " << this->message_id << endl <<
			"priority_flag = " << dec << (uint32_t) this->priority_flag << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->priority_flag << ")" << endl <<
			"schedule_delivery_time = " << this->schedule_delivery_time << endl <<
			"validity_period = " << this->validity_period << endl <<
			"replace_if_present_flag = " << dec << (uint32_t) this->replace_if_present_flag << " (0x" << internal << hex << setw(2) << setfill('0')  << (uint32_t) this->replace_if_present_flag << ")" << endl <<
			"data_coding = " << dec << (uint32_t) this->data_coding << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->data_coding << ")" << endl <<
			"sm_default_msg_id = " << dec << (uint32_t) this->sm_default_msg_id << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->sm_default_msg_id << ")" << endl;

	if (this->broadcast_area_identifier != NULL) this->broadcast_area_identifier->printTLVField();
	if (this->broadcast_content_type != NULL) this->broadcast_content_type->printTLVField();
	if (this->broadcast_rep_num != NULL) this->broadcast_rep_num->printTLVField();
	if (this->broadcast_frequency_interval != NULL) this->broadcast_frequency_interval->printTLVField();
	if (this->alert_on_msg_delivery != NULL) this->alert_on_msg_delivery->printTLVField();
	if (this->broadcast_channel_indicator != NULL) this->broadcast_channel_indicator->printTLVField();
	if (this->broadcast_content_type_info != NULL) this->broadcast_content_type_info->printTLVField();
	if (this->broadcast_message_class != NULL) this->broadcast_message_class->printTLVField();
	if (this->broadcast_service_group != NULL) this->broadcast_service_group->printTLVField();
	if (this->callback_num != NULL) this->callback_num->printTLVField();
	if (this->callback_num_atag != NULL) this->callback_num_atag->printTLVField();
	if (this->callback_num_pres_ind != NULL) this->callback_num_pres_ind->printTLVField();
	if (this->dest_addr_subunit != NULL) this->dest_addr_subunit->printTLVField();
	if (this->dest_port != NULL) this->dest_port->printTLVField();
	if (this->dest_subaddress != NULL) this->dest_subaddress->printTLVField();
	if (this->display_time != NULL) this->display_time->printTLVField();
	if (this->language_indicator != NULL) this->language_indicator->printTLVField();
	if (this->message_payload != NULL) this->message_payload->printTLVField();
	if (this->ms_validity != NULL) this->ms_validity->printTLVField();
	if (this->payload_type != NULL) this->payload_type->printTLVField();
	if (this->privacy_indicator != NULL) this->privacy_indicator->printTLVField();
	if (this->sms_signal != NULL) this->sms_signal->printTLVField();
	if (this->source_addr_subunit != NULL) this->source_addr_subunit->printTLVField();
	if (this->source_port != NULL) this->source_port->printTLVField();
	if (this->source_subaddress != NULL) this->source_subaddress->printTLVField();
	if (this->user_message_reference != NULL) this->user_message_reference->printTLVField();
}
