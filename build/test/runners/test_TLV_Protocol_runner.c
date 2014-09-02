/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
    CEXCEPTION_T e; \
    Try { \
      CMock_Init(); \
      setUp(); \
      TestFunc(); \
      CMock_Verify(); \
    } Catch(e) { TEST_ASSERT_EQUAL_HEX32_MESSAGE(CEXCEPTION_NONE, e, "Unhandled Exception!"); } \
  } \
  CMock_Destroy(); \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include "cmock.h"
#include <setjmp.h>
#include <stdio.h>
#include "CException.h"
#include "mock_rs232.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_openHexFile_should_return_0_if_fail_to_open_the_hex_file(void);
extern void test_openHexFile_should_return_1_if_able_to_open_the_hex_file(void);
extern void test_requestProgrammingMode_should_send_the_programming_mode_message_through_rs232(void);
extern void test_requestProgrammingMode_should_return_0_if_receiveByte_is_NACK(void);
extern void test_requestProgrammingMode_should_return_1_if_receiveByte_is_ACK(void);
extern void test_sendDataCode(void);


//=======Mock Management=====
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_rs232_Init();
}
static void CMock_Verify(void)
{
  mock_rs232_Verify();
}
static void CMock_Destroy(void)
{
  mock_rs232_Destroy();
}

//=======Test Reset Option=====
void resetTest()
{
  CMock_Verify();
  CMock_Destroy();
  tearDown();
  CMock_Init();
  setUp();
}


//=======MAIN=====
int main(void)
{
  Unity.TestFile = "test_TLV_Protocol.c";
  UnityBegin();
  RUN_TEST(test_openHexFile_should_return_0_if_fail_to_open_the_hex_file, 18);
  RUN_TEST(test_openHexFile_should_return_1_if_able_to_open_the_hex_file, 29);
  RUN_TEST(test_requestProgrammingMode_should_send_the_programming_mode_message_through_rs232, 40);
  RUN_TEST(test_requestProgrammingMode_should_return_0_if_receiveByte_is_NACK, 56);
  RUN_TEST(test_requestProgrammingMode_should_return_1_if_receiveByte_is_ACK, 73);
  RUN_TEST(test_sendDataCode, 90);

  return (UnityEnd());
}