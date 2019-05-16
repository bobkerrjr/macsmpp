/*
 * DataSm.h
 *
 *  Created on: Nov 2, 2011
 *      Author: Bob Kerr
 */

#ifndef DATASM_H_
#define DATASM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "EsmClass.h"
#include "NumberingPlanIndicator.h"

class DataSm: public SmppBody {
public:
	DataSm();
	DataSm(char*, uint32_t);
	~DataSm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								service_type;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	TypeOfNumber						dest_addr_ton;
	NumberingPlanIndicator				dest_addr_npi;
	char*								destination_addr;
	EsmClass							esm_class;
	uint8_t								registered_delivery;
	uint8_t								data_coding;
	//Optional TLV - Supported on both 3.4 and 5.0
	TagLengthValue*						source_port;
	TagLengthValue*						source_addr_subunit;
	TagLengthValue*						source_network_type;
	TagLengthValue*						source_bearer_type;
	TagLengthValue*						source_telematics_id;
	TagLengthValue*						destination_port;
	TagLengthValue*						dest_addr_subunit;
	TagLengthValue*						dest_network_type;
	TagLengthValue*						dest_bearer_type;
	TagLengthValue*						dest_telematics_id;
	TagLengthValue*						sar_msg_ref_num;
	TagLengthValue*						sar_total_segments;
	TagLengthValue*						sar_segment_seqnum;
	TagLengthValue*						more_messages_to_send;
	TagLengthValue*						qos_time_to_live;
	TagLengthValue*						payload_type;
	TagLengthValue*						message_payload;
	TagLengthValue*						set_dpf;
	TagLengthValue*						receipted_message_id;
	TagLengthValue*						message_state;
	TagLengthValue*						network_error_code;
	TagLengthValue*						user_message_reference;
	TagLengthValue*						privacy_indicator;
	TagLengthValue*						callback_num;
	TagLengthValue*						callback_num_pres_ind;
	TagLengthValue*						callback_num_atag;
	TagLengthValue*						source_subaddress;
	TagLengthValue*						dest_subaddress;
	TagLengthValue*						user_response_code;
	TagLengthValue*						display_time;
	TagLengthValue*						sms_signal;
	TagLengthValue*						ms_validity;
	TagLengthValue*						ms_msg_wait_facilities;
	TagLengthValue*						number_of_messages;
	TagLengthValue*						alert_on_msg_delivery;
	TagLengthValue*						language_indicator;
	TagLengthValue*						its_reply_type;
	TagLengthValue*						its_session_info;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						billing_identification;
	TagLengthValue*						dest_addr_np_country;
	TagLengthValue*						dest_addr_np_information;
	TagLengthValue*						dest_addr_np_resolution;
	TagLengthValue*						dest_network_id;
	TagLengthValue*						dest_node_id;
	TagLengthValue*						source_network_id;
	TagLengthValue*						source_node_id;
	TagLengthValue*						ussd_service_op;
};

#endif /* DATASM_H_ */
