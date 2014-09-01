#include "unity.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "mock_rs232.h"
#include <stdio.h>

#define COM_PORT 2

void setUp(void)
{
}

void tearDown(void)
{
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

