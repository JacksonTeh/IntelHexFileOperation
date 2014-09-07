#include "unity.h"
#include "mock_rs232.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "CustomTypeAssertion.h"








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



 RS232_SendByte_CMockExpectAndReturn(24, 4, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(25, 4, &receiveByte, 1, 1);



 result = requestProgrammingMode(receiveByte);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)29, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_requestProgrammingMode_should_return_1_if_ACK_is_receive_from_RS232(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte = ACK;

 int result;



 RS232_SendByte_CMockExpectAndReturn(40, 4, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(41, 4, &receiveByte, 1, 1);



 result = requestProgrammingMode(receiveByte);



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)45, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_readHexLineAndCreateIntelHex16Data_should_return_address_if_the_type_in_hex_line_is_04(void)

{

 FILE *hexFile;

 IntelHex16Data *data;

 int result, address = 0x0000;



 hexFile = fopen("test/data/Test02.hex", "r");



 if(hexFile == ((void *)0))

 {

  printf("error: cannot open the file Test.hex");

  exit(-1);

 }



 result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);



 UnityAssertEqualNumber((_U_SINT)((0x0030)), (_U_SINT)((address)), (((void *)0)), (_U_UINT)66, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((-1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)67, UNITY_DISPLAY_STYLE_INT);

}



void test_readHexLineAndCreateIntelHex16Data_should_return_0_if_the_type_in_hex_line_is_01(void)

{

 FILE *hexFile;

 IntelHex16Data *data;

 int result, address = 0x0000;



 hexFile = fopen("test/data/Test03.hex", "r");



 if(hexFile == ((void *)0))

 {

  printf("error: cannot open the file Test.hex");

  exit(-1);

 }



 result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((address)), (((void *)0)), (_U_UINT)86, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)87, UNITY_DISPLAY_STYLE_INT);

}



void test_readHexLineAndCreateIntelHex16Data_should_return_1_if_the_type_in_hex_line_is_other_than_04_and_01(void)

{

 FILE *hexFile;

 IntelHex16Data *data;

 int result, address = 0x0000;



 hexFile = fopen("test/data/Test04.hex", "r");



 if(hexFile == ((void *)0))

 {

  printf("error: cannot open the file Test.hex");

  exit(-1);

 }



 result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((address)), (((void *)0)), (_U_UINT)106, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)107, UNITY_DISPLAY_STYLE_INT);

 deleteIntelHex16Data(data);

}



void test_sendDataCode_should_return_1_if_ACK_is_receive_from_RS232(void)

{

 char buffer[1024] = ":10000000020E732745187327451873274518732761\n", receiveByte = ACK;

 int address = 0x0030, i, result;

 IntelHex16Data *data = createIntelHex16Data(buffer);

 TLV *tlvMessage = createProgramMessage(data, address);



 RS232_SendByte_CMockExpectAndReturn(118, 4, tlvMessage->type, 0);

 RS232_SendByte_CMockExpectAndReturn(119, 4, tlvMessage->length, 0);



 for(i = 0; i < tlvMessage->length; i++)

  RS232_SendByte_CMockExpectAndReturn(122, 4, tlvMessage->value[i], 0);



 RS232_PollComport_CMockExpectAndReturn(124, 4, &receiveByte, 1, 1);



 result = sendDataCode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)128, UNITY_DISPLAY_STYLE_INT);

 deleteIntelHex16Data(data);

 deleteTLV(tlvMessage);

}



void test_sendDataCode_should_return_0_if_NACK_is_receive_from_RS232(void)

{

 char buffer[1024] = ":10000000020E732745187327451873274518732761\n", receiveByte = NACK;

 int address = 0x0030, i, result;

 IntelHex16Data *data = createIntelHex16Data(buffer);

 TLV *tlvMessage = createProgramMessage(data, address);



 RS232_SendByte_CMockExpectAndReturn(140, 4, tlvMessage->type, 0);

 RS232_SendByte_CMockExpectAndReturn(141, 4, tlvMessage->length, 0);



 for(i = 0; i < tlvMessage->length; i++)

  RS232_SendByte_CMockExpectAndReturn(144, 4, tlvMessage->value[i], 0);



 RS232_PollComport_CMockExpectAndReturn(146, 4, &receiveByte, 1, 1);



 result = sendDataCode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)150, UNITY_DISPLAY_STYLE_INT);

 deleteIntelHex16Data(data);

 deleteTLV(tlvMessage);

}



void test_requestStartRunningMode_should_send_the_start_running_message_through_serial_transmit(void)

{

 TLV *tlvMessage = createStartRunningMessage();



 RS232_SendByte_CMockExpectAndReturn(159, 4, tlvMessage->type, 0);



 requestStartRunningMode();



 deleteTLV(tlvMessage);

}
