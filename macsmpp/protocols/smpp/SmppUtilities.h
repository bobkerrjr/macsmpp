/*
 * SmppUtilities.h
 *
 *  Created on: Nov 3, 2011
 *      Author: Bob Kerr
 */

#ifndef SMPPUTILITIES_H_
#define SMPPUTILITIES_H_

#define SMPP_SUPPORTED_VERSION(X)  														(((X==0x33)||(X==0x34)||(X==0x50)) ? true : false)
#define HEADER_SIZE																		16
#define SEQUENCE_NUMBER_MIN																0x00000001
#define SEQUENCE_NUMBER_MAX																0x7FFFFFFF
#define SYSTEM_ID_MAX																	16
#define PASSWORD_MAX																	9
#define SYSTEM_TYPE_MAX																	13
#define ADDRESS_RANGE_MAX																41
#define SERVICE_TYPE_MAX																6
#define SOURCE_ADDR_MAX																	21
#define DESTINATION_ADDR_MAX															21
#define SCHEDULE_DELIVERY_TIME_SIZE														17
#define VALIDITY_PERIOD_SIZE															17
#define SHORT_MESSAGE_MAX																254
#define MESSAGE_ID_V33_MAX																9
#define MESSAGE_ID_V34_V50_MAX															65
#define NUMBER_OF_DESTS_MAX																254
#define SME_ADDRESS																		1
#define DISTRIBUTION_LIST_NAME															2
#define DISTRIBUTION_LIST_MAX															21
#define DATA_SM_SOURCE_ADDR_MAX															65
#define DATA_SM_DESTINATION_ADDR_MAX													65
#define FINAL_DATE_MAX																	17
#define ALERT_NOTIFICATION_SOURCE_ADDR_MAX												65
#define ALERT_NOTIFICATION_ESME_ADDR_MAX												65
#define PARAM_NAME_SIZE																	32
#define PARAM_VALUE_SIZE																101


typedef enum timeFormat {
	SCHEDULE_DELIVERY_ABSOLUTE_TIME_FORMAT,
	SCHEDULE_DELIVERY_RELATIVE_TIME_FORMAT,
	VALIDITY_PERIOD_ABSOLUTE_TIME_FORMAT,
	VALIDITY_PERIOD_RELATIVE_TIME_FORMAT,
	FINAL_DATE_ABSOLUTE_TIME_FORMAT,
	FINAL_DATE_RELATIVE_TIME_FORMAT
}timeFormat;

char* SmppTimeDefinitions (timeFormat);

#endif /* SMPPUTILITIES_H_ */
