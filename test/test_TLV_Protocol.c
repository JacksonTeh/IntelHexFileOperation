#include "unity.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "CustomTypeAssertion.h"
#include "mock_rs232.h"
#include <stdio.h>

#define COM_PORT 4

void setUp(void)
{
}

void tearDown(void)
{
}

void test_requestProgrammingMode_should_return_0_if_NACK_is_receive_from_RS232(void)
{
	TLV *tlvMessage = createProgrammingMode();
	char receiveByte = NACK;
	int result;

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = requestProgrammingMode(receiveByte);

	TEST_ASSERT_EQUAL(0, result);

	deleteTLV(tlvMessage);
}

void test_requestProgrammingMode_should_return_1_if_ACK_is_receive_from_RS232(void)
{
	TLV *tlvMessage = createProgrammingMode();
	char receiveByte = ACK;
	int result;

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = requestProgrammingMode(receiveByte);

	TEST_ASSERT_EQUAL(1, result);

	deleteTLV(tlvMessage);
}

void test_readHexLineAndCreateIntelHex16Data_should_return_address_if_the_type_in_hex_line_is_04(void)
{
	FILE *hexFile;
	IntelHex16Data *data;
	int result, address = 0x0000;

	hexFile = fopen("C:/TDD Mini Project/IntelHexFileOperation/test/data/Test02.hex", "r");

	if(hexFile == NULL)
	{
		printf("error: cannot open the file Test.hex");
		exit(-1);
	}

	result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);

	TEST_ASSERT_EQUAL(0x0030, address);
	TEST_ASSERT_EQUAL(-1, result);
}

void test_readHexLineAndCreateIntelHex16Data_should_return_0_if_the_type_in_hex_line_is_01(void)
{
	FILE *hexFile;
	IntelHex16Data *data;
	int result, address = 0x0000;

	hexFile = fopen("C:/TDD Mini Project/IntelHexFileOperation/test/data/Test03.hex", "r");

	if(hexFile == NULL)
	{
		printf("error: cannot open the file Test.hex");
		exit(-1);
	}

	result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);

	TEST_ASSERT_EQUAL(0, address);
	TEST_ASSERT_EQUAL(0, result);
}

void test_readHexLineAndCreateIntelHex16Data_should_return_1_if_the_type_in_hex_line_is_other_than_04_and_01(void)
{
	FILE *hexFile;
	IntelHex16Data *data;
	int result, address = 0x0000;

	hexFile = fopen("C:/TDD Mini Project/IntelHexFileOperation/test/data/Test04.hex", "r");

	if(hexFile == NULL)
	{
		printf("error: cannot open the file Test.hex");
		exit(-1);
	}

	result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);

	TEST_ASSERT_EQUAL(0, address);
	TEST_ASSERT_EQUAL(1, result);
	deleteIntelHex16Data(data);
}

void test_sendDataCode_should_return_1_if_ACK_is_receive_from_RS232(void)
{
	char buffer[1024] = ":10000000020E732745187327451873274518732761\n", receiveByte = ACK;
	int address = 0x0030, i, result;
	IntelHex16Data *data = createIntelHex16Data(buffer);
	TLV *tlvMessage = createProgramMessage(data, address);

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->length, 0);

	for(i = 0; i < tlvMessage->length; i++)
		RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->value[i], 0);

	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = sendDataCode(tlvMessage, receiveByte);

	TEST_ASSERT_EQUAL(1, result);
	deleteIntelHex16Data(data);
	deleteTLV(tlvMessage);
}

void test_sendDataCode_should_return_0_if_NACK_is_receive_from_RS232(void)
{
	char buffer[1024] = ":10000000020E732745187327451873274518732761\n", receiveByte = NACK;
	int address = 0x0030, i, result;
	IntelHex16Data *data = createIntelHex16Data(buffer);
	TLV *tlvMessage = createProgramMessage(data, address);

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->length, 0);

	for(i = 0; i < tlvMessage->length; i++)
		RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->value[i], 0);

	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = sendDataCode(tlvMessage, receiveByte);

	TEST_ASSERT_EQUAL(0, result);
	deleteIntelHex16Data(data);
	deleteTLV(tlvMessage);
}

void test_requestStartRunningMode_should_send_the_start_running_message_through_serial_transmit(void)
{
	TLV *tlvMessage = createStartRunningMessage();

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);

	requestStartRunningMode();

	deleteTLV(tlvMessage);
}