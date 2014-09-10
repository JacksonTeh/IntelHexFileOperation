#include "unity.h"
#include "mock_rs232.h"
#include "IntelHex16Operation.h"
#include "CustomTypeAssertion.h"
#include "CException.h"






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





 hexFile = fopen("test/data/Test.hex", "r");





 if(hexFile == ((void *)0))

 {

  printf("error: cannot open the file Test.hex");

  exit(-1);

 }



 readLine(hexFile, buffer);





 fclose(hexFile);



 data = createIntelHex16Data(buffer);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)41);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)42);;};

 assertEqualReadLine(":020000040000FA\n", data, 43 );;



 deleteIntelHex16Data(data);

}



void test_readLine_should_read__second_string_of_line(void)

{

 char buffer[1024];

 FILE *hexFile;

 IntelHex16Data *data;





 hexFile = fopen("test/data/Test.hex", "r");





 if(hexFile == ((void *)0))

 {

  printf("error: cannot open the file Test.hex");

  exit(-1);

 }



 readLine(hexFile, buffer);

 readLine(hexFile, buffer);





 fclose(hexFile);



 data = createIntelHex16Data(buffer);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)72);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)73);;};

 assertEqualReadLine(":10000000020E732745187327451873274518732761\n", data, 74 );;



 deleteIntelHex16Data(data);

}



void test_createIntelHex16Data_should_throw_an_exception_if_first_character_is_not_colon(void)

{

 char buffer[1024] = "020000040000FA\n";

 FILE *hexFile;

 IntelHex16Data *data;

 unsigned int err;



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame)

 {

  data = createIntelHex16Data(buffer);

  UnityFail( ("Should generate an exception due to first character is not colon."), (_U_UINT)89);;

 }else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { err = CExceptionFrames[MY_ID].Exception; err=err; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A))

 {

  UnityAssertEqualNumber((_U_SINT)((ERR_NO_COLON)), (_U_SINT)((err)), ("Expected ERR_NO_COLON exception"), (_U_UINT)92, UNITY_DISPLAY_STYLE_INT);

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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)110);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)111);;};

 UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)112, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)128);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)129);;};

 UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)130, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)146);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)147);;};

 UnityAssertEqualNumber((_U_SINT)((-1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)148, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)164);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)165);;};

 UnityAssertEqualNumber((_U_SINT)((-1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)166, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)182);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)183);;};

 UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)184, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)200);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)201);;};

 UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)202, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)218);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)219);;};

 UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)220, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)236);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)237);;};

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)238, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)254);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)255);;};

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)256, UNITY_DISPLAY_STYLE_INT);



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



 UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)273, UNITY_DISPLAY_STYLE_INT);



 byte = getLSByteAndShiftRight(&result);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)277);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)278);;};

 UnityAssertEqualNumber((_U_SINT)((16)), (_U_SINT)((byte)), (((void *)0)), (_U_UINT)279, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((result)), (((void *)0)), (_U_UINT)280, UNITY_DISPLAY_STYLE_INT);



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



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)295);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)296);;};



 dataHigh = getByteFromIntelHex16Data(data, 5);

 dataLow = getByteFromIntelHex16Data(data, 6);

 address = (dataHigh << 8) | dataLow;



 deleteIntelHex16Data(data);



 data = createIntelHex16Data(buffer2);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)306);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)307);;};



 tlvMessage = createProgramMessage(data, address);



 if ((((tlvMessage)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)311);;};



 char value[] = {0x10, 0x00, 0x30, 0x00,

     0x45, 0x18, 0x73, 0x27, 0x45, 0x18, 0x73, 0x27,

     0x45, 0x18, 0x73, 0x27, 0x45, 0x18, 0x73, 0x27,

     0x04};



 assertEqualTLV(tlvMessage->type, tlvMessage->length, value, tlvMessage, 318 );;



 deleteIntelHex16Data(data);

 deleteTLV(tlvMessage);

}



void test_createProgramMessage_should_raise_an_exception_if_wrong_checksum(void)

{

 int address, dataHigh, dataLow;

 char buffer1[1024] = ":020000040000FA\n", buffer2[1024] = ":10000000020E732745187327421873274518732761\n";

 IntelHex16Data *data;

 TLV *tlvMessage;

 unsigned int err;



 data = createIntelHex16Data(buffer1);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)334);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)335);;};



 dataHigh = getByteFromIntelHex16Data(data, 5);

 dataLow = getByteFromIntelHex16Data(data, 6);

 address = (dataHigh << 8) | dataLow;



 deleteIntelHex16Data(data);



 data = createIntelHex16Data(buffer2);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)345);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)346);;};



 { jmp_buf *PrevFrame, NewFrame; unsigned int MY_ID = (0); PrevFrame = CExceptionFrames[(0)].pFrame; CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame); CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); if (_setjmp(NewFrame) == 0) { if (&PrevFrame)

 {

  tlvMessage = createProgramMessage(data, address);

  UnityFail( ("Should generate an exception due to wrong checksum."), (_U_UINT)351);;

 }else { } CExceptionFrames[MY_ID].Exception = (0x5A5A5A5A); } else { err = CExceptionFrames[MY_ID].Exception; err=err; } CExceptionFrames[MY_ID].pFrame = PrevFrame; } if (CExceptionFrames[(0)].Exception != (0x5A5A5A5A))

 {

  UnityAssertEqualNumber((_U_SINT)((ERR_WRONG_CHECKSUM)), (_U_SINT)((err)), ("Expected ERR_WRONG_CHECKSUM exception"), (_U_UINT)354, UNITY_DISPLAY_STYLE_INT);

  printf("Success: Exception generated. Error code: %d.\n", err);

 }



 deleteIntelHex16Data(data);

 deleteTLV(tlvMessage);

}



void test_createProgrammingMode_should_create_programming_mode_message(void)

{

 TLV *tlvMessage = createProgrammingMode();



 UnityAssertEqualNumber((_U_SINT)((PROGRAMMING_MODE)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)366, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_createStartRunningMessage_should_create_start_running_message(void)

{

 TLV *tlvMessage = createStartRunningMessage();



 UnityAssertEqualNumber((_U_SINT)((START_RUNNING)), (_U_SINT)((tlvMessage->type)), (((void *)0)), (_U_UINT)375, UNITY_DISPLAY_STYLE_INT);



 deleteTLV(tlvMessage);

}



void test_sendTLV_should_send_TLV_byte_by_byte(void)

{

 int address, dataHigh, dataLow, i;

 char buffer1[1024] = ":020000040000FA\n", buffer2[1024] = ":10000000020E732745187327451873274518732761\n", value[100];

 IntelHex16Data *data;

 TLV *tlvMessage;

 unsigned int err;



 data = createIntelHex16Data(buffer1);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)390);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)391);;};



 dataHigh = getByteFromIntelHex16Data(data, 5);

 dataLow = getByteFromIntelHex16Data(data, 6);

 address = (dataHigh << 8) | dataLow;



 deleteIntelHex16Data(data);



 data = createIntelHex16Data(buffer2);



 if ((((data)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)401);;};

 if ((((data->line)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)402);;};



 tlvMessage = createProgramMessage(data, address);



 if ((((tlvMessage)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)406);;};



 RS232_SendByte_CMockExpectAndReturn(408, 4, tlvMessage->type, 0);

 RS232_SendByte_CMockExpectAndReturn(409, 4, tlvMessage->length, 0);



 for(i = 0; i < tlvMessage->length; i++)

  RS232_SendByte_CMockExpectAndReturn(412, 4, tlvMessage->value[i], 0);



 sendTLV(tlvMessage);



 deleteIntelHex16Data(data);

 deleteTLV(tlvMessage);

}
