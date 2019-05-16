/*
 * DeliverSm.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#include "DeliverSm.h"
#include <iomanip>
#include <iostream>
using namespace std;

DeliverSm::DeliverSm() {
#ifdef DEBUG
	cout << "DeliverSm::DeliverSm()" << endl;
#endif
	this->init();
}

DeliverSm::DeliverSm(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "DeliverSm::DeliverSm(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

DeliverSm::~DeliverSm() {
#ifdef DEBUG
	cout << "DeliverSm::~DeliverSm()" << endl;
#endif
	this->destroy();
}

void DeliverSm::destroy() {
	if (this->service_type != NULL) delete this->service_type;
	if (this->source_addr != NULL) delete this->source_addr;
	if (this->destination_addr != NULL) delete this->destination_addr;
	if (this->short_message != NULL) delete this->short_message;
	//TLV
	if (this->callback_num != NULL) delete this->callback_num;
	if (this->callback_num_atag != NULL) delete this->callback_num_atag;
	if (this->callback_num_pres_ind != NULL) delete this->callback_num_pres_ind;
	if (this->dest_addr_np_country != NULL) delete this->dest_addr_np_country;
	if (this->dest_addr_np_information != NULL) delete this->dest_addr_np_information;
	if (this->dest_addr_np_resolution != NULL) delete this->dest_addr_np_resolution;
	if (this->dest_addr_subunit != NULL) delete this->dest_addr_subunit;
	if (this->dest_network_id != NULL) delete this->dest_network_id;
	if (this->dest_node_id != NULL) delete this->dest_node_id;
	if (this->dest_subaddress != NULL) delete this->dest_subaddress;
	if (this->destination_port != NULL) delete this->destination_port;
	if (this->dpf_result != NULL) delete this->dpf_result;
	if (this->its_reply_type != NULL) delete this->its_reply_type;
	if (this->its_session_info != NULL) delete this->its_session_info;
	if (this->language_indicator != NULL) delete this->language_indicator;
	if (this->message_payload != NULL) delete this->message_payload;
	if (this->message_state != NULL) delete this->message_state;
	if (this->network_error_code != NULL) delete this->network_error_code;
	if (this->payload_type != NULL) delete this->payload_type;
	if (this->privacy_indicator != NULL) delete this->privacy_indicator;
	if (this->receipted_message_id != NULL) delete this->receipted_message_id;
	if (this->sar_msg_ref_num != NULL) delete this->sar_msg_ref_num;
	if (this->sar_segment_seqnum != NULL) delete this->sar_segment_seqnum;
	if (this->sar_total_segments != NULL) delete this->sar_total_segments;
	if (this->source_addr_subunit != NULL) delete this->source_addr_subunit;
	if (this->source_network_id != NULL) delete this->source_network_id;
	if (this->source_node_id != NULL) delete this->source_node_id;
	if (this->source_port != NULL) delete this->source_port;
	if (this->source_subaddress != NULL) delete this->source_subaddress;
	if (this->user_message_reference != NULL) delete this->user_message_reference;
	if (this->user_response_code != NULL) delete this->user_response_code;
	if (this->ussd_service_op != NULL) delete this->ussd_service_op;
	this->init();
}

void DeliverSm::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x07; // 3.3, 3.4 and 5.0
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->dest_addr_ton.setFieldName("dest_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->dest_addr_npi.setFieldName("dest_addr_npi");
	this->esm_class.setMessageFlow(0x02);
	this->service_type = NULL;
	this->source_addr = NULL;
	this->destination_addr = NULL;
	this->short_message = NULL;
	//TLV
	this->callback_num = NULL;
	this->callback_num_atag = NULL;
	this->callback_num_pres_ind = NULL;
	this->dest_addr_np_country = NULL;
	this->dest_addr_np_information = NULL;
	this->dest_addr_np_resolution = NULL;
	this->dest_addr_subunit = NULL;
	this->dest_network_id = NULL;
	this->dest_node_id = NULL;
	this->dest_subaddress = NULL;
	this->destination_port = NULL;
	this->dpf_result = NULL;
	this->its_reply_type = NULL;
	this->its_session_info = NULL;
	this->language_indicator = NULL;
	this->message_payload = NULL;
	this->message_state = NULL;
	this->network_error_code = NULL;
	this->payload_type = NULL;
	this->privacy_indicator = NULL;
	this->receipted_message_id = NULL;
	this->sar_msg_ref_num = NULL;
	this->sar_segment_seqnum = NULL;
	this->sar_total_segments = NULL;
	this->source_addr_subunit = NULL;
	this->source_network_id = NULL;
	this->source_node_id = NULL;
	this->source_port = NULL;
	this->source_subaddress = NULL;
	this->user_message_reference = NULL;
	this->user_response_code = NULL;
	this->ussd_service_op = NULL;
}

void DeliverSm::pduDecode(char * buffer, uint32_t commandLength) {
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
	this->source_addr_ton.setMyUnsignedByte((char) buffer[x++]);
	this->source_addr_npi.setMyUnsignedByte((char) buffer[x++]);

	//Copy source_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->source_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->source_addr[i] = buffer[x+i];
	this->source_addr[i] = 0;
	x+=++i;

	//Copy ton and npi values
	this->dest_addr_ton.setMyUnsignedByte((char) buffer[x++]);
	this->dest_addr_npi.setMyUnsignedByte((char) buffer[x++]);

	//Copy destination_addr string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->destination_addr = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->destination_addr[i] = buffer[x+i];
	this->destination_addr[i] = 0;
	x+=++i;

	//Copy esm_class, protocol_id, priority_flag, schedule_delivery_time and validity_period values
	this->esm_class.setMyUnsignedByte((char) buffer[x++]);
	this->protocol_id = (char) buffer[x++];
	this->priority_flag = (char) buffer[x++];
	this->schedule_delivery_time = (char) buffer[x++];
	this->validity_period = (char) buffer[x++];

	//Copy registered_delivery, replace_if_present_flag, data_coding, sm_default_msg_id and sm_length values
	this->registered_delivery = (char) buffer[x++];
	this->replace_if_present_flag = (char) buffer[x++];
	this->data_coding = (char) buffer[x++];
	this->sm_default_msg_id = (char) buffer[x++];
	this->sm_length = (char) buffer[x++];

	//Copy short_message string to pduFinal
	i = this->sm_length;
	if (i==0)
		this->short_message = NULL;
	else
		this->short_message = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;i < this->sm_length;i++)
		this->short_message[i] = buffer[x+i];
	x+=this->sm_length;

	//Check if exist any optional parameter
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		case TLV_USER_MESSAGE_REFERENCE:
			this->user_message_reference = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_SOURCE_PORT:
			this->source_port = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_DESTINATION_PORT:
			this->destination_port = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_SAR_MSG_REF_NUM:
			this->sar_msg_ref_num = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_SAR_TOTAL_SEGMENTS:
			this->sar_total_segments = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_SAR_SEGMENT_SEQNUM:
			this->sar_segment_seqnum = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_USER_RESPONSE_CODE:
			this->user_response_code = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_PRIVACY_INDICATOR:
			this->privacy_indicator = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_PAYLOAD_TYPE:
			this->payload_type = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_MESSAGE_PAYLOAD:
			this->message_payload = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_CALLBACK_NUM:
			this->callback_num = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_SOURCE_SUBADDRESS:
			this->source_subaddress = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_DEST_SUBADDRESS:
			this->dest_subaddress = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_LANGUAGE_INDICATOR:
			this->language_indicator = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_ITS_SESSION_INFO:
			this->its_session_info = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_NETWORK_ERROR_CODE:
			this->network_error_code = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_MESSAGE_STATE:
			this->message_state = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_RECEIPTED_MESSAGE_ID:
			this->receipted_message_id = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFE; //It's not version 3.3
			break;
		case TLV_CALLBACK_NUM_ATAG:
			this->callback_num_atag = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_CALLBACK_NUM_PRES_IND:
			this->callback_num_pres_ind = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_ADDR_NP_COUNTRY:
			this->dest_addr_np_country = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_ADDR_NP_INFORMATION:
			this->dest_addr_np_information = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_ADDR_NP_RESOLUTION:
			this->dest_addr_np_resolution = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_ADDR_SUBUNIT:
			this->dest_addr_subunit = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_NETWORK_ID:
			this->dest_network_id = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DEST_NODE_ID:
			this->dest_node_id = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_DPF_RESULT:
			this->dpf_result = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_ITS_REPLY_TYPE:
			this->its_reply_type = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_SOURCE_ADDR_SUBUNIT:
			this->source_addr_subunit = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_SOURCE_NETWORK_ID:
			this->source_network_id = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_SOURCE_NODE_ID:
			this->source_node_id = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
			break;
		case TLV_USSD_SERVICE_OP:
			this->ussd_service_op = pTemp;
			x += pTemp->getBufSize();
			this->myPossibleVersion &= 0xFC; //It's not version 3.3 nor 3.4
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

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void DeliverSm::printPduInfo() {
	int i;
	cout << "service_type = " << this->service_type << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			this->dest_addr_ton << endl <<
			this->dest_addr_npi << endl <<
			"destination_addr = " << this->destination_addr << endl <<
			this->esm_class << endl <<
			"protocol_id = " << dec << (uint32_t) this->protocol_id << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->protocol_id << ")" << endl <<
			"priority_flag = " << dec << (uint32_t) this->priority_flag << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->priority_flag << ")" << endl <<
			"schedule_delivery_time = " << dec << (uint32_t) this->schedule_delivery_time << endl <<
			"validity_period = " << dec << (uint32_t) this->validity_period << endl <<
			"registered_delivery = " << dec << (uint32_t) this->registered_delivery << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->registered_delivery << ")" << endl <<
			"replace_if_present_flag = " << dec << (uint32_t) this->replace_if_present_flag << " (0x" << internal << hex << setw(2) << setfill('0')  << (uint32_t) this->replace_if_present_flag << ")" << endl <<
			"data_coding = " << dec << (uint32_t) this->data_coding << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->data_coding << ")" << endl <<
			"sm_default_msg_id = " << dec << (uint32_t) this->sm_default_msg_id << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->sm_default_msg_id << ")" << endl <<
			"sm_length = " << dec << (uint32_t) this->sm_length << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->sm_length << ")" << endl;
	cout << "short_message = ";
	for(i=0; i < this->sm_length; i++)
		cout << this->short_message[i];
	cout << endl;

	if (this->callback_num != NULL) this->callback_num->printTLVField();
	if (this->callback_num_atag != NULL) this->callback_num_atag->printTLVField();
	if (this->callback_num_pres_ind != NULL) this->callback_num_pres_ind->printTLVField();
	if (this->dest_addr_np_country != NULL) this->dest_addr_np_country->printTLVField();
	if (this->dest_addr_np_information != NULL) this->dest_addr_np_information->printTLVField();
	if (this->dest_addr_np_resolution != NULL) this->dest_addr_np_resolution->printTLVField();
	if (this->dest_addr_subunit != NULL) this->dest_addr_subunit->printTLVField();
	if (this->dest_network_id != NULL) this->dest_network_id->printTLVField();
	if (this->dest_node_id != NULL) this->dest_node_id->printTLVField();
	if (this->dest_subaddress != NULL) this->dest_subaddress->printTLVField();
	if (this->destination_port != NULL) this->destination_port->printTLVField();
	if (this->dpf_result != NULL) this->dpf_result->printTLVField();
	if (this->its_reply_type != NULL) this->its_reply_type->printTLVField();
	if (this->its_session_info != NULL) this->its_session_info->printTLVField();
	if (this->language_indicator != NULL) this->language_indicator->printTLVField();
	if (this->message_payload != NULL) this->message_payload->printTLVField();
	if (this->message_state != NULL) this->message_state->printTLVField();
	if (this->network_error_code != NULL) this->network_error_code->printTLVField();
	if (this->payload_type != NULL) this->payload_type->printTLVField();
	if (this->privacy_indicator != NULL) this->privacy_indicator->printTLVField();
	if (this->receipted_message_id != NULL) this->receipted_message_id->printTLVField();
	if (this->sar_msg_ref_num != NULL) this->sar_msg_ref_num->printTLVField();
	if (this->sar_segment_seqnum != NULL) this->sar_segment_seqnum->printTLVField();
	if (this->sar_total_segments != NULL) this->sar_total_segments->printTLVField();
	if (this->source_addr_subunit != NULL) this->source_addr_subunit->printTLVField();
	if (this->source_network_id != NULL) this->source_network_id->printTLVField();
	if (this->source_node_id != NULL) this->source_node_id->printTLVField();
	if (this->source_port != NULL) this->source_port->printTLVField();
	if (this->source_subaddress != NULL) this->source_subaddress->printTLVField();
	if (this->user_message_reference != NULL) this->user_message_reference->printTLVField();
	if (this->user_response_code != NULL) this->user_response_code->printTLVField();
	if (this->ussd_service_op != NULL) this->ussd_service_op->printTLVField();
}
