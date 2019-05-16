/*
 * QueryMsgDetailsRespResp.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: Bob Kerr
 */

#include "QueryMsgDetailsResp.h"
#include <iostream>
#include <iomanip>
using namespace std;

QueryMsgDetailsResp::QueryMsgDetailsResp() {
#ifdef DEBUG
	cout << "QueryMsgDetailsResp::QueryMsgDetailsResp()" << endl;
#endif
	this->init();
}

QueryMsgDetailsResp::QueryMsgDetailsResp(char* buffer, uint32_t commandLength) {
#ifdef DEBUG
	cout << "QueryMsgDetailsResp::QueryMsgDetailsResp(char* buffer, uint32_t commandLength)" << endl;
#endif
	this->init();
	this->pduDecode(buffer, commandLength);
}

QueryMsgDetailsResp::~QueryMsgDetailsResp() {
#ifdef DEBUG
	cout << "QueryMsgDetailsResp::~QueryMsgDetailsResp()" << endl;
#endif
	this->destroy();
}

void QueryMsgDetailsResp::destroy() {
	if (this->source_addr != NULL) delete this->source_addr;
	if (this->dest_address != NULL) delete [] this->dest_address;
	if (this->final_date != NULL) delete this->final_date;
	if (this->msgid != NULL) delete this->msgid;
	if (this->schedule_delivery_time != NULL) delete this->schedule_delivery_time;
	if (this->service_type != NULL) delete this->service_type;
	if (this->short_message != NULL) delete this->short_message;
	if (this->validity_period != NULL) delete this->validity_period;
	this->init();
}

void QueryMsgDetailsResp::init() {
	//Initial values
	this->numOfByteErrors = 0;
	this->isValid = true;
	this->myPossibleVersion = 0x01; // 3.3
	this->source_addr_ton.setFieldName("source_addr_ton");
	this->source_addr_npi.setFieldName("source_addr_npi");
	this->source_addr = NULL;
	this->dest_address = NULL;
	this->final_date = NULL;
	this->msgid = NULL;
	this->schedule_delivery_time = NULL;
	this->service_type = NULL;
	this->short_message = NULL;
	this->validity_period = NULL;
}

void QueryMsgDetailsResp::pduDecode(char * buffer, uint32_t commandLength) {
	int i = 0;
	int j = 0;
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

	//Copy number_of_dests value
	this->number_of_dests = (char) buffer[x++];

	//Copy dest_address strings to pduFinal
	j = this->number_of_dests;
	if (j==0)
		this->dest_address = NULL;
	else
		this->dest_address = (DestinationAddress*) new DestinationAddress[j];
	//TODO: Check if null, and treat
	if (this->dest_address != NULL)
		for(j=0;j < this->number_of_dests;j++)
			x += this->dest_address[j].pduDestAddrDecode((char*)(buffer + x));
	else
		x++;

	//Copy protocol_id and protocol_id values
	this->protocol_id = (char) buffer[x++];
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

	//Copy registered_delivery_flag, data_coding and sm_length values
	this->registered_delivery_flag = (char) buffer[x++];
	this->data_coding = (char) buffer[x++];
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

	//Copy msgid string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->msgid = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->msgid[i] = buffer[x+i];
	this->msgid[i] = 0;
	x+=++i;

	//Copy final_date string to pduFinal
	for(i=0;buffer[x+i]!=0;i++); i++;
	this->final_date = (char*) new char[i];
	//TODO: Check if null, and treat
	for(i=0;buffer[x+i]!=0;i++)
		this->final_date[i] = buffer[x+i];
	this->final_date[i] = 0;
	x+=++i;

	//Copy message_status and error_code values
	this->message_status = (char) buffer[x++];
	this->error_code = (char) buffer[x++];

	//Check if exist any optional parameter
	/* Version 3.3 of SMPP does not support TLV
	while(commandLength > x)
	{
		TagLengthValue* pTemp;
		uint16_t tagTemp;
		pTemp = new TagLengthValue((char *)(buffer+x));
		tagTemp = pTemp->getParameterTag();
		switch(tagTemp)
		{
		default:
			x += pTemp->getBufSize();
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
	*/

	//TODO: Include LOG
#ifdef DEBUG
	if(commandLength == x)
		cout << "Done! commandLength = " << commandLength << ", x = " << x << endl;
	else cout << "Error! commandLength = " << commandLength << ", x = " << x << endl;
#endif
}

void QueryMsgDetailsResp::printPduInfo() {
	int i = 0;
	cout << "service_type = " << this->service_type << endl <<
			this->source_addr_ton << endl <<
			this->source_addr_npi << endl <<
			"source_addr = " << this->source_addr << endl <<
			"number_of_dests = " << dec << (uint32_t) this->number_of_dests << endl;

	if (this->dest_address != NULL) {
		for(i=0; i < this->number_of_dests; i++) {
			cout << "dest_address[" << dec << i << "]" << endl;
			this->dest_address[i].printDestAddInfo();
		}
	}

	cout << "protocol_id = " << dec << (uint32_t) this->protocol_id << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->protocol_id << ")" << endl <<
			"priority_flag = " << dec << (uint32_t) this->priority_flag << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->priority_flag << ")" << endl <<
			"schedule_delivery_time = " << this->schedule_delivery_time << endl <<
			"validity_period = " << this->validity_period << endl <<
			"registered_delivery_flag = " << dec << (uint32_t) this->registered_delivery_flag << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->registered_delivery_flag << ")" << endl <<
			"data_coding = " << dec << (uint32_t) this->data_coding << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->data_coding << ")" << endl <<
			"sm_length = " << dec << (uint32_t) this->sm_length << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->sm_length << ")" << endl;

	cout << "short_message = ";
	for(i=0; i < this->sm_length; i++)
		cout << this->short_message[i];
	cout << endl;

	cout << "msgid = " << this->msgid << endl <<
			"final_date = " << this->final_date << endl <<
			"message_status = " << dec << (uint32_t) this->message_status << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->message_status << ")" << endl <<
			"error_code = " << dec << (uint32_t) this->error_code << " (0x" << internal << hex << setw(2) << setfill('0') << (uint32_t) this->error_code << ")" << endl;
}
