#include "unity.h"
#include "RunTLV.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"

#include "rs232.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_(void)
{
    int result;

    result = tlvProtocol();

    TEST_ASSERT_EQUAL(0, result);
}
