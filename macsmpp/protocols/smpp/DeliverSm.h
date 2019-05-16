/*
 * DeliverSm.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Bob Kerr
 */

#ifndef DELIVERSM_H_
#define DELIVERSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "EsmClass.h"
#include "NumberingPlanIndicator.h"

class DeliverSm: public SmppBody {
public:
	DeliverSm();
	DeliverSm(char*, uint32_t);
	~DeliverSm();
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
	uint8_t								protocol_id;
	uint8_t								priority_flag;
	uint8_t								schedule_delivery_time;
	uint8_t								validity_period;
	uint8_t								registered_delivery;
	uint8_t								replace_if_present_flag;
	uint8_t								data_coding;
	uint8_t								sm_default_msg_id;
	uint8_t								sm_length;
	char*								short_message;
	//Optional TLV - Supported on both 3.4 and 5.0
	TagLengthValue*						user_message_reference;
	TagLengthValue*						source_port;
	TagLengthValue*						destination_port;
	TagLengthValue*						sar_msg_ref_num;
	TagLengthValue*						sar_total_segments;
	TagLengthValue*						sar_segment_seqnum;
	TagLengthValue*						user_response_code;
	TagLengthValue*						privacy_indicator;
	TagLengthValue*						payload_type;
	TagLengthValue*						message_payload;
	TagLengthValue*						callback_num;
	TagLengthValue*						source_subaddress;
	TagLengthValue*						dest_subaddress;
	TagLengthValue*						language_indicator;
	TagLengthValue*						its_session_info;
	TagLengthValue*						network_error_code;
	TagLengthValue*						message_state;
	TagLengthValue*						receipted_message_id;
	//Optional TLV - Supported on 5.0 only
	TagLengthValue*						callback_num_atag;
	TagLengthValue*						callback_num_pres_ind;
	TagLengthValue*						dest_addr_np_country;
	TagLengthValue*						dest_addr_np_information;
	TagLengthValue*						dest_addr_np_resolution;
	TagLengthValue*						dest_addr_subunit;
	TagLengthValue*						dest_network_id;
	TagLengthValue*						dest_node_id;
	TagLengthValue*						dpf_result;
	TagLengthValue*						its_reply_type;
	TagLengthValue*						source_addr_subunit;
	TagLengthValue*						source_network_id;
	TagLengthValue*						source_node_id;
	TagLengthValue*						ussd_service_op;
};

#endif /* DELIVERSM_H_ */
