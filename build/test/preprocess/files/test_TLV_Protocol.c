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



void test_requestProgrammingMode_should_send_the_programming_mode_message_through_rs232(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte;



 RS232_SendByte_CMockExpectAndReturn(22, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(23, 2, &receiveByte, 1, 1);



 requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)27, UNITY_DISPLAY_STYLE_INT);





 deleteTLV(tlvMessage);

}



void test_requestProgrammingMode_should_return_0_if_receiveByte_is_NACK(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte = NACK;

 int result;



 RS232_SendByte_CMockExpectAndReturn(39, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(40, 2, &receiveByte, 1, 1);



 result = requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)44, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)45, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_requestProgrammingMode_should_return_1_if_receiveByte_is_ACK(void)

{

 TLV *tlvMessage = createProgrammingMode();

 char receiveByte = ACK;

 int result;



 RS232_SendByte_CMockExpectAndReturn(56, 2, tlvMessage->type, 0);

 RS232_PollComport_CMockExpectAndReturn(57, 2, &receiveByte, 1, 1);



 result = requestProgrammingMode(tlvMessage, receiveByte);



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)61, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)62, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}
