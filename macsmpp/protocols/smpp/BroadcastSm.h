/*
 * BroadcastSm.h
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#ifndef BROADCASTSM_H_
#define BROADCASTSM_H_

#include "SmppBody.h"
#include "TypeOfNumber.h"
#include "NumberingPlanIndicator.h"

class BroadcastSm: public SmppBody {
public:
	BroadcastSm();
	BroadcastSm(char*, uint32_t);
	~BroadcastSm();
	void init();
	void destroy();
	void pduDecode(char *, uint32_t);
	void printPduInfo();
private:
	char*								service_type;
	TypeOfNumber						source_addr_ton;
	NumberingPlanIndicator				source_addr_npi;
	char*								source_addr;
	char*								message_id;
	uint8_t								priority_flag;
	char*								schedule_delivery_time;
	char*								validity_period;
	uint8_t								replace_if_present_flag;
	uint8_t								data_coding;
	uint8_t								sm_default_msg_id;
	//Mandatory TLV
	TagLengthValue*						broadcast_area_identifier;
	TagLengthValue*						broadcast_content_type;
	TagLengthValue*						broadcast_rep_num;
	TagLengthValue*						broadcast_frequency_interval;
	//Optional TLV
	TagLengthValue*						alert_on_msg_delivery;
	TagLengthValue*						broadcast_channel_indicator;
	TagLengthValue*						broadcast_content_type_info;
	TagLengthValue*						broadcast_message_class;
	TagLengthValue*						broadcast_service_group;
	TagLengthValue*						callback_num;
	TagLengthValue*						callback_num_atag;
	TagLengthValue*						callback_num_pres_ind;
	TagLengthValue*						dest_addr_subunit;
	TagLengthValue*						dest_subaddress;
	TagLengthValue*						dest_port;
	TagLengthValue*						display_time;
	TagLengthValue*						language_indicator;
	TagLengthValue*						message_payload;
	TagLengthValue*						ms_validity;
	TagLengthValue*						payload_type;
	TagLengthValue*						privacy_indicator;
	TagLengthValue*						sms_signal;
	TagLengthValue*						source_addr_subunit;
	TagLengthValue*						source_port;
	TagLengthValue*						source_subaddress;
	TagLengthValue*						user_message_reference;
};

#endif /* BROADCASTSM_H_ */
