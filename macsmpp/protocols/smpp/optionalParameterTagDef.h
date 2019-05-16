/*
 * optionalParameterTagDef.h
 *
 *  Created on: Oct 19, 2011
 *                                                                                                Author: Bob Kerr
 *
 * Description: This file defines the SMPP supported Optional Parameters
 *                                 and their associated Tag Values. This item can be found
 *                                 on spec file, chapter 5.3.2
 */

#ifndef OPTIONALPARAMETERTAGDEF_H_
#define OPTIONALPARAMETERTAGDEF_H_

#define TLV_DEST_ADDR_SUBUNIT                                0x0005 //        3.4        5.0
#define TLV_DEST_NETWORK_TYPE                                0x0006 //        3.4        5.0
#define TLV_DEST_BEARER_TYPE                                 0x0007 //        3.4        5.0
#define TLV_DEST_TELEMATICS_ID                               0x0008 //        3.4        5.0
#define TLV_SOURCE_ADDR_SUBUNIT                              0x000D //        3.4        5.0
#define TLV_SOURCE_NETWORK_TYPE                              0x000E //        3.4        5.0
#define TLV_SOURCE_BEARER_TYPE                               0x000F //        3.4        5.0
#define TLV_SOURCE_TELEMATICS_ID                             0x0010 //        3.4        5.0
#define TLV_QOS_TIME_TO_LIVE                                 0x0017 //        3.4        5.0
#define TLV_PAYLOAD_TYPE                                     0x0019 //        3.4        5.0
#define TLV_ADDITIONAL_STATUS_INFO_TEXT                      0x001D //        3.4        5.0
#define TLV_RECEIPTED_MESSAGE_ID                             0x001E //        3.4        5.0
#define TLV_MS_MSG_WAIT_FACILITIES                           0x0030 //        3.4        5.0
#define TLV_PRIVACY_INDICATOR                                0x0201 //        3.4        5.0
#define TLV_SOURCE_SUBADDRESS                                0x0202 //        3.4        5.0
#define TLV_DEST_SUBADDRESS                                  0x0203 //        3.4        5.0
#define TLV_USER_MESSAGE_REFERENCE                           0x0204 //        3.4        5.0
#define TLV_USER_RESPONSE_CODE                               0x0205 //        3.4        5.0
#define TLV_SOURCE_PORT                                      0x020A //        3.4        5.0
#define TLV_DESTINATION_PORT                                 0x020B //        3.4        5.0
#define TLV_SAR_MSG_REF_NUM                                  0x020C //        3.4        5.0
#define TLV_LANGUAGE_INDICATOR                               0x020D //        3.4        5.0
#define TLV_SAR_TOTAL_SEGMENTS                               0x020E //        3.4        5.0
#define TLV_SAR_SEGMENT_SEQNUM                               0x020F //        3.4        5.0
#define TLV_SC_INTERFACE_VERSION                             0x0210 //        3.4        5.0
#define TLV_CALLBACK_NUM_PRES_IND                            0x0302 //        3.4        5.0
#define TLV_CALLBACK_NUM_ATAG                                0x0303 //        3.4        5.0
#define TLV_NUMBER_OF_MESSAGES                               0x0304 //        3.4        5.0
#define TLV_CALLBACK_NUM                                     0x0381 //        3.4        5.0
#define TLV_DPF_RESULT                                       0x0420 //        3.4        5.0
#define TLV_SET_DPF                                          0x0421 //        3.4        5.0
#define TLV_MS_AVAILABILITY_STATUS                           0x0422 //        3.4        5.0
#define TLV_NETWORK_ERROR_CODE                               0x0423 //        3.4        5.0
#define TLV_MESSAGE_PAYLOAD                                  0x0424 //        3.4        5.0
#define TLV_DELIVERY_FAILURE_REASON                          0x0425 //        3.4        5.0
#define TLV_MORE_MESSAGES_TO_SEND                            0x0426 //        3.4        5.0
#define TLV_MESSAGE_STATE                                    0x0427 //        3.4        5.0
#define TLV_CONGESTION_STATE                                 0x0428 //                   5.0
#define TLV_USSD_SERVICE_OP                                  0x0501 //        3.4        5.0
#define TLV_BROADCAST_CHANNEL_INDICATOR                      0x0601 //                   5.0
#define TLV_BROADCAST_CONTENT_TYPE                           0x0602 //                   5.0
#define TLV_BROADCAST_CONTENT_TYPE_INFO                      0x0603 //                   5.0
#define TLV_BROADCAST_MESSAGE_CLASS                          0x0604 //                   5.0
#define TLV_BROADCAST_REP_NUM                                0x0605 //                   5.0
#define TLV_BROADCAST_FREQUENCY_INTERVAL                     0x0606 //                   5.0
#define TLV_BROADCAST_AREA_IDENTIFIER                        0x0607 //                   5.0
#define TLV_BROADCAST_ERROR_STATUS                           0x0608 //                   5.0
#define TLV_BROADCAST_AREA_SUCCESS                           0x0609 //                   5.0
#define TLV_BROADCAST_END_TIME                               0x060A //                   5.0
#define TLV_BROADCAST_SERVICE_GROUP                          0x060B //                   5.0
#define TLV_BILLING_IDENTIFICATION                           0x060C //                   5.0
#define TLV_SOURCE_NETWORK_ID                                0x060D //                   5.0
#define TLV_DEST_NETWORK_ID                                  0x060E //                   5.0
#define TLV_SOURCE_NODE_ID                                   0x060F //                   5.0
#define TLV_DEST_NODE_ID                                     0x0610 //                   5.0
#define TLV_DEST_ADDR_NP_RESOLUTION                          0x0611 //                   5.0
#define TLV_DEST_ADDR_NP_INFORMATION                         0x0612 //                   5.0
#define TLV_DEST_ADDR_NP_COUNTRY                             0x0613 //                   5.0
#define TLV_DISPLAY_TIME                                     0x1201 //        3.4        5.0
#define TLV_SMS_SIGNAL                                       0x1203 //        3.4        5.0
#define TLV_MS_VALIDITY                                      0x1204 //        3.4        5.0
#define TLV_ALERT_ON_MESSAGE_DELIVERY                        0x130C //        3.4        5.0
#define TLV_ITS_REPLY_TYPE                                   0x1380 //        3.4        5.0
#define TLV_ITS_SESSION_INFO                                 0x1383 //        3.4        5.0


/*
	case TLV_DEST_ADDR_SUBUNIT:
	case TLV_DEST_NETWORK_TYPE:
	case TLV_DEST_BEARER_TYPE:
	case TLV_DEST_TELEMATICS_ID:
	case TLV_SOURCE_ADDR_SUBUNIT:
	case TLV_SOURCE_NETWORK_TYPE:
	case TLV_SOURCE_BEARER_TYPE:
	case TLV_SOURCE_TELEMATICS_ID:
	case TLV_QOS_TIME_TO_LIVE:
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


"dest_addr_subunit"
"dest_network_type"
"dest_bearer_type"
"dest_telematics_id"
"source_addr_subunit"
"source_network_type"
"source_bearer_type"
"source_telematics_id"
"qos_time_to_live"
"payload_type"
"additional_status_info_text"
"receipted_message_id"
"ms_msg_wait_facilities"
"privacy_indicator"
"source_subaddress"
"dest_subaddress"
"user_message_reference"
"user_response_code"
"source_port"
"destination_port"
"sar_msg_ref_num"
"language_indicator"
"sar_total_segments"
"sar_segment_seqnum"
"sc_interface_version"
"callback_num_pres_ind"
"callback_num_atag"
"number_of_messages"
"callback_num"
"dpf_result"
"set_dpf"
"ms_availability_status"
"network_error_code"
"message_payload"
"delivery_failure_reason"
"more_messages_to_send"
"message_state"
"congestion_state"
"ussd_service_op"
"broadcast_channel_indicator"
"broadcast_content_type"
"broadcast_content_type_info"
"broadcast_message_class"
"broadcast_rep_num"
"broadcast_frequency_interval"
"broadcast_area_identifier"
"broadcast_error_status"
"broadcast_area_success"
"broadcast_end_time"
"broadcast_service_group"
"billing_identification"
"source_network_id"
"dest_network_id"
"source_node_id"
"dest_node_id"
"dest_addr_np_resolution"
"dest_addr_np_information"
"dest_addr_np_country"
"display_time"
"sms_signal"
"ms_validity"
"alert_on_message_delivery"
"its_reply_type"
"its_session_info"
*/
#endif /* OPTIONALPARAMETERTAGDEF_H_ */
