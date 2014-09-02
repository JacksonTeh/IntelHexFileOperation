#include "unity.h"
#include "mock_rs232.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"










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



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((openHexFile(hexFile))), (((void *)0)), (_U_UINT)24, UNITY_DISPLAY_STYLE_INT);



 fclose(hexFile);

}



void test_openHexFile_should_return_1_if_able_to_open_the_hex_file(void)

{

 FILE *hexFile;



 hexFile = fopen("LEDBlink.hex", "r");



 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((openHexFile(hexFile))), (((void *)0)), (_U_UINT)35, UNITY_DISPLAY_STYLE_INT);



 fclose(hexFile);

}



void test_requestProgrammingMode_should_send_the_programming_mode_message_through_rs232(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte;



 RS232_SendByte_CMockExpectAndReturn(45, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(46, 2, &receiveByte, 1, 1);



 requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)50, UNITY_DISPLAY_STYLE_INT);





 deleteTLV(tlvMessage);

}



void test_requestProgrammingMode_should_return_0_if_receiveByte_is_NACK(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte = NACK;

 int result;



 RS232_SendByte_CMockExpectAndReturn(62, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(63, 2, &receiveByte, 1, 1);



 result = requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)67, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)68, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_requestProgrammingMode_should_return_1_if_receiveByte_is_ACK(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte = ACK;

 int result;



 RS232_SendByte_CMockExpectAndReturn(79, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(80, 2, &receiveByte, 1, 1);



 result = requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)84, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)85, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_sendDataCode(void)

{



}
