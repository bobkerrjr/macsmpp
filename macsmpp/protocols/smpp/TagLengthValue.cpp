/*
 * TagLengthValue.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: Bob Kerr
 */

#include "optionalParameterTagDef.h"
#include "TagLengthValue.h"
#include "../../utilities/endianSwap.h"
#include <iostream>
#include <iomanip>
using namespace std;
extern void endianSwap(uint16_t &);
extern void endianSwap(uint32_t &);

TagLengthValue::TagLengthValue()
{
#ifdef DEBUG
	cout << "TagLengthValue::TagLengthValue()" << endl;
#endif
	this->init();
}

TagLengthValue::TagLengthValue(char * buffer) {
#ifdef DEBUG
	cout << "TagLengthValue::TagLengthValue(char * buffer)" << endl;
#endif
	this->init();
	this->pduDecode(buffer);
}

TagLengthValue::~TagLengthValue()
{
#ifdef DEBUG
	cout << "TagLengthValue::~TagLengthValue()" << endl;
#endif
	this->destroy();
}

void TagLengthValue::destroy() {
	if (this->value!=NULL) delete this->value;
	this->init();
}

void TagLengthValue::init() {
	parameterTag = 0;
	length = 0;
	value = NULL;
	tlvName = NULL;
	bufSize = 0;
}

void TagLengthValue::printTLVField()
{
	int i;
	cout << this->tlvName << "->parameterTag = 0x" << internal << setw(4) << setfill('0') << hex << this->parameterTag << endl <<
			this->tlvName << "->length = " << dec << this->length << endl;
	switch (this->parameterTag)
	{
        case TLV_DEST_ADDR_SUBUNIT:
        case TLV_SOURCE_ADDR_SUBUNIT:
          cout << this->tlvName << "->value = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) this->value[0];
          if (this->value[0] == 0)
            cout << " (Unknown)" << endl;
          else if (this->value[0] == 1)
            cout << " (MS Display)" << endl;
          else if (this->value[0] == 2)
            cout << " (Mobile Equipment)" << endl;
          else if (this->value[0] == 3)
            cout << " (Smart Card 1)" << endl;
          else if (this->value[0] == 4)
            cout << " (External Unit 1)" << endl;
          else cout << " (Reserved)" << endl;
          break;
        case TLV_DEST_NETWORK_TYPE:
        case TLV_SOURCE_NETWORK_TYPE:
          cout << this->tlvName << "->value = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) this->value[0];
          if (this->value[0] == 0)
            cout << " (Unknown)" << endl;
          else if (this->value[0] == 1)
            cout << " (GSM)" << endl;
          else if (this->value[0] == 2)
            cout << " (ANSI-136/TDMA)" << endl;
          else if (this->value[0] == 3)
            cout << " (IS-95/CDMA)" << endl;
          else if (this->value[0] == 4)
            cout << " (PDC)" << endl;
          else if (this->value[0] == 5)
            cout << " (PHS)" << endl;
          else if (this->value[0] == 6)
            cout << " (iDEN)" << endl;
          else if (this->value[0] == 7)
            cout << " (AMPS)" << endl;
          else if (this->value[0] == 8)
            cout << " (Paging Network)" << endl;
          else cout << " (Reserved)" << endl;
          break;
        case TLV_DEST_BEARER_TYPE:
        case TLV_SOURCE_BEARER_TYPE:
          cout << this->tlvName << "->value = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) this->value[0];
          if (this->value[0] == 0)
            cout << " (Unknown)" << endl;
          else if (this->value[0] == 1)
            cout << " (SMS)" << endl;
          else if (this->value[0] == 2)
            cout << " (Circuit Switched Data - CSD)" << endl;
          else if (this->value[0] == 3)
            cout << " (Packet Data)" << endl;
          else if (this->value[0] == 4)
            cout << " (USSD)" << endl;
          else if (this->value[0] == 5)
            cout << " (CDPD)" << endl;
          else if (this->value[0] == 6)
            cout << " (DataTAC)" << endl;
          else if (this->value[0] == 7)
            cout << " (FLEX/ReFLEX)" << endl;
          else if (this->value[0] == 8)
            cout << " (Cell Broadcast)" << endl;
          else cout << " (Reserved)" << endl;
          break;

        case TLV_DEST_TELEMATICS_ID:
        case TLV_SOURCE_TELEMATICS_ID:

        case TLV_QOS_TIME_TO_LIVE:
          {
            uint32_t * pTime_to_live = (uint32_t*) &this->value[0];
            uint32_t time_to_live = (uint32_t) *pTime_to_live;
            endianSwap(time_to_live);
            cout << this->tlvName << "->value = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) time_to_live << " (" << dec << (uint32_t) time_to_live << " seconds)" << endl;
          }
          break;
        case TLV_PAYLOAD_TYPE:
        case TLV_ADDITIONAL_STATUS_INFO_TEXT:
        case TLV_RECEIPTED_MESSAGE_ID:
        case TLV_MS_MSG_WAIT_FACILITIES:
        case TLV_PRIVACY_INDICATOR:
        case TLV_SOURCE_SUBADDRESS:
        case TLV_DEST_SUBADDRESS:
        case TLV_USER_MESSAGE_REFERENCE:
        case TLV_USER_RESPONSE_CODE:
        case TLV_SOURCE_PORT:
        case TLV_DESTINATION_PORT:
        case TLV_SAR_MSG_REF_NUM:
        case TLV_LANGUAGE_INDICATOR:
        case TLV_SAR_TOTAL_SEGMENTS:
        case TLV_SAR_SEGMENT_SEQNUM:
        case TLV_SC_INTERFACE_VERSION:
        case TLV_CALLBACK_NUM_PRES_IND:
        case TLV_CALLBACK_NUM_ATAG:
        case TLV_NUMBER_OF_MESSAGES:
        case TLV_CALLBACK_NUM:
        case TLV_DPF_RESULT:
        case TLV_SET_DPF:
        case TLV_MS_AVAILABILITY_STATUS:
        case TLV_NETWORK_ERROR_CODE:
        case TLV_MESSAGE_PAYLOAD:
        case TLV_DELIVERY_FAILURE_REASON:
        case TLV_MORE_MESSAGES_TO_SEND:
        case TLV_MESSAGE_STATE:
        case TLV_CONGESTION_STATE:
        case TLV_USSD_SERVICE_OP:
        case TLV_BROADCAST_CHANNEL_INDICATOR:
        case TLV_BROADCAST_CONTENT_TYPE:
        case TLV_BROADCAST_CONTENT_TYPE_INFO:
        case TLV_BROADCAST_MESSAGE_CLASS:
        case TLV_BROADCAST_REP_NUM:
        case TLV_BROADCAST_FREQUENCY_INTERVAL:
        case TLV_BROADCAST_AREA_IDENTIFIER:
        case TLV_BROADCAST_ERROR_STATUS:
        case TLV_BROADCAST_AREA_SUCCESS:
        case TLV_BROADCAST_END_TIME:
        case TLV_BROADCAST_SERVICE_GROUP:
        case TLV_BILLING_IDENTIFICATION:
        case TLV_SOURCE_NETWORK_ID:
        case TLV_DEST_NETWORK_ID:
        case TLV_SOURCE_NODE_ID:
        case TLV_DEST_NODE_ID:
        case TLV_DEST_ADDR_NP_RESOLUTION:
        case TLV_DEST_ADDR_NP_INFORMATION:
        case TLV_DEST_ADDR_NP_COUNTRY:
        case TLV_DISPLAY_TIME:
        case TLV_SMS_SIGNAL:
        case TLV_MS_VALIDITY:
        case TLV_ALERT_ON_MESSAGE_DELIVERY:
        case TLV_ITS_REPLY_TYPE:
        case TLV_ITS_SESSION_INFO:
          for (i=0; i < this->length; i++)
                  cout << this->tlvName << "->value[" << dec << i <<"] = 0x" << internal << setw(2) << setfill('0') << hex << (uint32_t) this->value[i] << endl;
          break;
	}
}

void TagLengthValue::defineTLVName() {
	switch (this->parameterTag)
	{
	case TLV_DEST_ADDR_SUBUNIT:
		this->tlvName = (char*) "dest_addr_subunit";
		break;
	case TLV_DEST_NETWORK_TYPE:
		this->tlvName = (char*) "dest_network_type";
		break;
	case TLV_DEST_BEARER_TYPE:
		this->tlvName = (char*) "dest_bearer_type";
		break;
	case TLV_DEST_TELEMATICS_ID:
		this->tlvName = (char*) "dest_telematics_id";
		break;
	case TLV_SOURCE_ADDR_SUBUNIT:
		this->tlvName = (char*) "source_addr_subunit";
		break;
	case TLV_SOURCE_NETWORK_TYPE:
		this->tlvName = (char*) "source_network_type";
		break;
	case TLV_SOURCE_BEARER_TYPE:
		this->tlvName = (char*)"source_bearer_type";
		break;
	case TLV_SOURCE_TELEMATICS_ID:
		this->tlvName = (char*) "source_telematics_id";
		break;
	case TLV_QOS_TIME_TO_LIVE:
		this->tlvName = (char*) "qos_time_to_live";
		break;
	case TLV_PAYLOAD_TYPE:
		this->tlvName = (char*) "payload_type";
		break;
	case TLV_ADDITIONAL_STATUS_INFO_TEXT:
		this->tlvName = (char*) "additional_status_info_text";
		break;
	case TLV_RECEIPTED_MESSAGE_ID:
		this->tlvName = (char*) "receipted_message_id";
		break;
	case TLV_MS_MSG_WAIT_FACILITIES:
		this->tlvName = (char*) "ms_msg_wait_facilities";
		break;
	case TLV_PRIVACY_INDICATOR:
		this->tlvName = (char*) "privacy_indicator";
		break;
	case TLV_SOURCE_SUBADDRESS:
		this->tlvName = (char*) "source_subaddress";
		break;
	case TLV_DEST_SUBADDRESS:
		this->tlvName = (char*) "dest_subaddress";
		break;
	case TLV_USER_MESSAGE_REFERENCE:
		this->tlvName = (char*) "user_message_reference";
		break;
	case TLV_USER_RESPONSE_CODE:
		this->tlvName = (char*) "user_response_code";
		break;
	case TLV_SOURCE_PORT:
		this->tlvName = (char*) "source_port";
		break;
	case TLV_DESTINATION_PORT:
		this->tlvName = (char*) "destination_port";
		break;
	case TLV_SAR_MSG_REF_NUM:
		this->tlvName = (char*) "sar_msg_ref_num";
		break;
	case TLV_LANGUAGE_INDICATOR:
		this->tlvName = (char*) "language_indicator";
		break;
	case TLV_SAR_TOTAL_SEGMENTS:
		this->tlvName = (char*) "sar_total_segments";
		break;
	case TLV_SAR_SEGMENT_SEQNUM:
		this->tlvName = (char*) "sar_segment_seqnum";
		break;
	case TLV_SC_INTERFACE_VERSION:
		this->tlvName = (char*) "sc_interface_version";
		break;
	case TLV_CALLBACK_NUM_PRES_IND:
		this->tlvName = (char*) "callback_num_pres_ind";
		break;
	case TLV_CALLBACK_NUM_ATAG:
		this->tlvName = (char*) "callback_num_atag";
		break;
	case TLV_NUMBER_OF_MESSAGES:
		this->tlvName = (char*) "number_of_messages";
		break;
	case TLV_CALLBACK_NUM:
		this->tlvName = (char*) "callback_num";
		break;
	case TLV_DPF_RESULT:
		this->tlvName = (char*) "dpf_result";
		break;
	case TLV_SET_DPF:
		this->tlvName = (char*) "set_dpf";
		break;
	case TLV_MS_AVAILABILITY_STATUS:
		this->tlvName = (char*) "ms_availability_status";
		break;
	case TLV_NETWORK_ERROR_CODE:
		this->tlvName = (char*) "network_error_code";
		break;
	case TLV_MESSAGE_PAYLOAD:
		this->tlvName = (char*) "message_payload";
		break;
	case TLV_DELIVERY_FAILURE_REASON:
		this->tlvName = (char*) "delivery_failure_reason";
		break;
	case TLV_MORE_MESSAGES_TO_SEND:
		this->tlvName = (char*) "more_messages_to_send";
		break;
	case TLV_MESSAGE_STATE:
		this->tlvName = (char*) "message_state";
		break;
	case TLV_CONGESTION_STATE:
		this->tlvName = (char*) "congestion_state";
		break;
	case TLV_USSD_SERVICE_OP:
		this->tlvName = (char*) "ussd_service_op";
		break;
	case TLV_BROADCAST_CHANNEL_INDICATOR:
		this->tlvName = (char*) "broadcast_channel_indicator";
		break;
	case TLV_BROADCAST_CONTENT_TYPE:
		this->tlvName = (char*) "broadcast_content_type";
		break;
	case TLV_BROADCAST_CONTENT_TYPE_INFO:
		this->tlvName = (char*) "broadcast_content_type_info";
		break;
	case TLV_BROADCAST_MESSAGE_CLASS:
		this->tlvName = (char*) "broadcast_message_class";
		break;
	case TLV_BROADCAST_REP_NUM:
		this->tlvName = (char*) "broadcast_rep_num";
		break;
	case TLV_BROADCAST_FREQUENCY_INTERVAL:
		this->tlvName = (char*) "broadcast_frequency_interval";
		break;
	case TLV_BROADCAST_AREA_IDENTIFIER:
		this->tlvName = (char*) "broadcast_area_identifier";
		break;
	case TLV_BROADCAST_ERROR_STATUS:
		this->tlvName = (char*) "broadcast_error_status";
		break;
	case TLV_BROADCAST_AREA_SUCCESS:
		this->tlvName = (char*) "broadcast_area_success";
		break;
	case TLV_BROADCAST_END_TIME:
		this->tlvName = (char*) "broadcast_end_time";
		break;
	case TLV_BROADCAST_SERVICE_GROUP:
		this->tlvName = (char*) "broadcast_service_group";
		break;
	case TLV_BILLING_IDENTIFICATION:
		this->tlvName = (char*) "billing_identification";
		break;
	case TLV_SOURCE_NETWORK_ID:
		this->tlvName = (char*) "source_network_id";
		break;
	case TLV_DEST_NETWORK_ID:
		this->tlvName = (char*) "dest_network_id";
		break;
	case TLV_SOURCE_NODE_ID:
		this->tlvName = (char*) "source_node_id";
		break;
	case TLV_DEST_NODE_ID:
		this->tlvName = (char*) "dest_node_id";
		break;
	case TLV_DEST_ADDR_NP_RESOLUTION:
		this->tlvName = (char*) "dest_addr_np_resolution";
		break;
	case TLV_DEST_ADDR_NP_INFORMATION:
		this->tlvName = (char*) "dest_addr_np_information";
		break;
	case TLV_DEST_ADDR_NP_COUNTRY:
		this->tlvName = (char*) "dest_addr_np_country";
		break;
	case TLV_DISPLAY_TIME:
		this->tlvName = (char*) "display_time";
		break;
	case TLV_SMS_SIGNAL:
		this->tlvName = (char*) "sms_signal";
		break;
	case TLV_MS_VALIDITY:
		this->tlvName = (char*) "ms_validity";
		break;
	case TLV_ALERT_ON_MESSAGE_DELIVERY:
		this->tlvName = (char*) "alert_on_message_delivery";
		break;
	case TLV_ITS_REPLY_TYPE:
		this->tlvName = (char*) "its_reply_type";
		break;
	case TLV_ITS_SESSION_INFO:
		this->tlvName = (char*) "its_session_info";
		break;
	default:
		this->tlvName = (char*) "unknown";
		break;
	}

}

void TagLengthValue::pduDecode(char* buffer) {
	int i = 0, j = 0;
	uint16_t* z;

	//Destroy pointers that are already instantiated, in case of re-decoding
	this->destroy();

	//Copy TAG to TLV
	z = (uint16_t*) &buffer[bufSize];
	this->parameterTag = (uint16_t) *z;
	endianSwap(this->parameterTag);
	this->bufSize+=sizeof(uint16_t);

	//Copy LENGTH to TLV
	z = (uint16_t*) &buffer[this->bufSize];
	this->length = *z;
	endianSwap(this->length);
	this->bufSize+=sizeof(uint16_t);

	//Copy VALUE to TLV
	j = this->length;
	this->value = (unsigned char*) new char[j];
	//TODO: Check if null, and treat
	for (i = 0;i<j;i++)
		this->value[i] = buffer[this->bufSize+i];
	this->bufSize+=i;

	this->defineTLVName();
}
