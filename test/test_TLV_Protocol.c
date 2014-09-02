#include "unity.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "CustomTypeAssertion.h"
#include "mock_rs232.h"
#include <stdio.h>

#define COM_PORT 2
#define IntelHexFile "LEDBlink.hex"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_openHexFile_should_return_0_if_fail_to_open_the_hex_file(void)
{
	FILE *hexFile;

	hexFile = fopen("TEST.text", "r");

	TEST_ASSERT_EQUAL(0, openHexFile(hexFile));

	fclose(hexFile);
}

void test_openHexFile_should_return_1_if_able_to_open_the_hex_file(void)
{
	FILE *hexFile;

	hexFile = fopen(IntelHexFile, "r");

	TEST_ASSERT_EQUAL(1, openHexFile(hexFile));

	fclose(hexFile);
}

void test_requestProgrammingMode_should_send_the_programming_mode_message_through_rs232(void)
{
	TLV *tlvMessage = createProgrammingMode();
	char receiveByte;

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	requestProgrammingMode(tlvMessage, receiveByte);

	TEST_ASSERT_EQUAL(PROGRAMMING_MODE, tlvMessage->type);
	// TEST_ASSERT_EQUAL(ACK, receiveByte);

	deleteTLV(tlvMessage);
}

void test_requestProgrammingMode_should_return_0_if_receiveByte_is_NACK(void)
{
	TLV *tlvMessage = createProgrammingMode();
	char receiveByte = NACK;
	int result;

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = requestProgrammingMode(tlvMessage, receiveByte);

	TEST_ASSERT_EQUAL(PROGRAMMING_MODE, tlvMessage->type);
	TEST_ASSERT_EQUAL(0, result);

	deleteTLV(tlvMessage);
}

void test_requestProgrammingMode_should_return_1_if_receiveByte_is_ACK(void)
{
	TLV *tlvMessage = createProgrammingMode();
	char receiveByte = ACK;
	int result;

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_PollComport_ExpectAndReturn(COM_PORT, &receiveByte, 1, 1);

	result = requestProgrammingMode(tlvMessage, receiveByte);

	TEST_ASSERT_EQUAL(PROGRAMMING_MODE, tlvMessage->type);
	TEST_ASSERT_EQUAL(1, result);

	deleteTLV(tlvMessage);
}

void test_sendDataCode(void)
{
	FILE *hexFile;
	TLV *tlv;
	char *buffer;

	
}