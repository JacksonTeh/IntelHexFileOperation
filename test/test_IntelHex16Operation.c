#include "unity.h"
#include "IntelHex16Operation.h"
#include "CustomTypeAssertion.h"
#include "CException.h"
#include "mock_rs232.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_readLine_should_read_first_string_of_line(void)
{
	char buffer[1024];
	FILE *hexFile;
	IntelHex16Data *data;

	// Open a file
	hexFile = fopen("test/data/Test.hex", "r");

	// Make sure that the file is successfully opened
	if(hexFile == NULL)
	{
		printf("error: cannot open the file Test.hex");
		exit(-1);	// Terminate the program immediately
	}

	readLine(hexFile, buffer);

	// Close the file
	fclose(hexFile);

	data = createIntelHex16Data(buffer);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL_ReadLine(":020000040000FA\n", data);

	deleteIntelHex16Data(data);
}

void test_readLine_should_read__second_string_of_line(void)
{
	char buffer[1024];
	FILE *hexFile;
	IntelHex16Data *data;

	// Open a file
	hexFile = fopen("test/data/Test.hex", "r");

	// Make sure that the file is successfully opened
	if(hexFile == NULL)
	{
		printf("error: cannot open the file Test.hex");
		exit(-1);	// Terminate the program immediately
	}

	readLine(hexFile, buffer);
	readLine(hexFile, buffer);

	// Close the file
	fclose(hexFile);

	data = createIntelHex16Data(buffer);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL_ReadLine(":10000000020E732745187327451873274518732761\n", data);

	deleteIntelHex16Data(data);
}

void test_createIntelHex16Data_should_throw_an_exception_if_first_character_is_not_colon(void)
{
	char buffer[1024] = "020000040000FA\n";
	FILE *hexFile;
	IntelHex16Data *data;
	CEXCEPTION_T err;

	Try
	{
		data = createIntelHex16Data(buffer);
		TEST_FAIL_MESSAGE("Should generate an exception due to first character is not colon.");
	}Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_NO_COLON, err, "Expected ERR_NO_COLON exception");
		printf("Success: Exception generated. Error code: %d.\n", err);
	}

	deleteIntelHex16Data(data);
}

void test_getByteFromIntelHex16Data_given_index_1_should_get_the_first_byte(void)
{
	int result;
	char buffer[1024] = ":020000040000FA\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getByteFromIntelHex16Data(data, 1);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(2, result);

	deleteIntelHex16Data(data);
}

void test_getByteFromIntelHex16Data_given_index_4_should_get_the_forth_byte(void)
{
	int result;
	char buffer[1024] = ":020000040000FA\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getByteFromIntelHex16Data(data, 4);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(4, result);

	deleteIntelHex16Data(data);
}

void test_getByteFromIntelHex16Data_given_index_0_should_return_minus_1(void)
{
	int result;
	char buffer[1024] = ":020000040000FA\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getByteFromIntelHex16Data(data, 0);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(-1, result);

	deleteIntelHex16Data(data);
}

void test_getByteFromIntelHex16Data_given_index_exceed_the_no_of_byte_of_the_line_should_return_minus_1(void)
{
	int result;
	char buffer[1024] = ":020000040000FA\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getByteFromIntelHex16Data(data, 8);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(-1, result);

	deleteIntelHex16Data(data);
}

void test_getLengthFromIntelHex16Data_should_get_length_from_INTEL_HEX_FILE(void)
{
	int result;
	char buffer[1024] = ":10000000020E732745187327451873274518732761\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getLengthFromIntelHex16Data(data);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(16, result);

	deleteIntelHex16Data(data);
}

void test_getTypeFromIntelHex16Data_should_get_type_from_INTEL_HEX_FILE(void)
{
	int result;
	char buffer[1024]= ":020000040000FA";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getTypeFromIntelHex16Data(data);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(4, result);

	deleteIntelHex16Data(data);
}

void test_getAddressFromIntelHex16Data_should_get_address_from_INTEL_HEX_FILE(void)
{
	int result;
	char buffer[1024] = ":100010004518732745187327451873274518732704\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getAddressFromIntelHex16Data(data);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(16, result);

	deleteIntelHex16Data(data);
}

void test_verifyCheckSumOfIntelHex16Data_should_return_1_if_no_error(void)
{
	int result;
	char buffer[1024] = ":10000000020E732745187327451873274518732761\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = verifyCheckSumOfIntelHex16Data(data);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(1, result);

	deleteIntelHex16Data(data);
}

void test_verifyCheckSumOfIntelHex16Data_should_return_0_if_got_error(void)
{
	int result;
	char buffer[1024] = ":020000040000FB\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = verifyCheckSumOfIntelHex16Data(data);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(0, result);

	deleteIntelHex16Data(data);
}

void test_getLSByteAndShiftRight_should_shift_the_address_to_the_right(void)
{
	int byte;
	int long result;
	char buffer[1024] = ":100010004518732745187327451873274518732704\n";
	FILE *hexFile;
	IntelHex16Data *data;

	data = createIntelHex16Data(buffer);

	result = getAddressFromIntelHex16Data(data);

	TEST_ASSERT_EQUAL(16, result);

	byte = getLSByteAndShiftRight(&result);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);
	TEST_ASSERT_EQUAL(16, byte);
	TEST_ASSERT_EQUAL(0, result);

	deleteIntelHex16Data(data);
}

void test_createProgramMessage_should_create_message_for_the_program(void)
{
	int address, dataHigh, dataLow;
	char buffer1[1024] = ":020000040030F7\n", buffer2[1024] = ":100010004518732745187327451873274518732704\n";
	FILE *hexFile;
	IntelHex16Data *data;
	TLV *tlvMessage;

	data = createIntelHex16Data(buffer1);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	dataHigh = getByteFromIntelHex16Data(data, 5);
	dataLow = getByteFromIntelHex16Data(data, 6);
	address = (dataHigh << 8) | dataLow;

	deleteIntelHex16Data(data);

	data = createIntelHex16Data(buffer2);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	tlvMessage = createProgramMessage(data, address);

	TEST_ASSERT_NOT_NULL(tlvMessage);

	char value[] = {0x10, 0x00, 0x30, 0x00,								//address
					0x45, 0x18, 0x73, 0x27, 0x45, 0x18, 0x73, 0x27,		//data
					0x45, 0x18, 0x73, 0x27, 0x45, 0x18, 0x73, 0x27,
					0x04};												//checksum

	TEST_ASSERT_EQUAL_TLV(tlvMessage->type, tlvMessage->length, value, tlvMessage);

	deleteIntelHex16Data(data);
	deleteTLV(tlvMessage);
}

void test_createProgramMessage_should_raise_an_exception_if_wrong_checksum(void)
{
	int address, dataHigh, dataLow;
	char buffer1[1024] = ":020000040000FA\n", buffer2[1024] = ":10000000020E732745187327421873274518732761\n";
	IntelHex16Data *data;
	TLV *tlvMessage;
	CEXCEPTION_T err;

	data = createIntelHex16Data(buffer1);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	dataHigh = getByteFromIntelHex16Data(data, 5);
	dataLow = getByteFromIntelHex16Data(data, 6);
	address = (dataHigh << 8) | dataLow;

	deleteIntelHex16Data(data);

	data = createIntelHex16Data(buffer2);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	Try
	{
		tlvMessage = createProgramMessage(data, address);
		TEST_FAIL_MESSAGE("Should generate an exception due to wrong checksum.");
	}Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_WRONG_CHECKSUM, err, "Expected ERR_WRONG_CHECKSUM exception");
		printf("Success: Exception generated. Error code: %d.\n", err);
	}

	deleteIntelHex16Data(data);
	deleteTLV(tlvMessage);
}

void test_createProgrammingMode_should_create_programming_mode_message(void)
{
	TLV *tlvMessage = createProgrammingMode();

	TEST_ASSERT_EQUAL(PROGRAMMING_MODE, tlvMessage->type);

	deleteTLV(tlvMessage);
}

void test_createStartRunningMessage_should_create_start_running_message(void)
{
	TLV *tlvMessage = createStartRunningMessage();

	TEST_ASSERT_EQUAL(START_RUNNING, tlvMessage->type);

	deleteTLV(tlvMessage);
}

void test_sendTLV_should_send_TLV_byte_by_byte(void)
{
	int address, dataHigh, dataLow, i;
	char buffer1[1024] = ":020000040000FA\n", buffer2[1024] = ":10000000020E732745187327451873274518732761\n", value[100];
	IntelHex16Data *data;
	TLV *tlvMessage;
	CEXCEPTION_T err;

	data = createIntelHex16Data(buffer1);
	
	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	dataHigh = getByteFromIntelHex16Data(data, 5);
	dataLow = getByteFromIntelHex16Data(data, 6);
	address = (dataHigh << 8) | dataLow;

	deleteIntelHex16Data(data);

	data = createIntelHex16Data(buffer2);

	TEST_ASSERT_NOT_NULL(data);
	TEST_ASSERT_NOT_NULL(data->line);

	tlvMessage = createProgramMessage(data, address);

	TEST_ASSERT_NOT_NULL(tlvMessage);

	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->type, 0);
	RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->length, 0);

	for(i = 0; i < tlvMessage->length; i++)
		RS232_SendByte_ExpectAndReturn(COM_PORT, tlvMessage->value[i], 0);

	sendTLV(tlvMessage);

	deleteIntelHex16Data(data);
	deleteTLV(tlvMessage);
}