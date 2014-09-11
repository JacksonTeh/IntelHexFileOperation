#include <stdio.h>
#include "unity.h"
#include "CustomTypeAssertion.h"

void assertEqualReadLine(char *expectedLine, IntelHex16Data *data, int line)
{
	char buffer[128];
	int i;
	//TEST_ASSERT_EQUAL(x, coor->x);
	//UNITY_TEST_ASSERT_EQUAL_INT(x, coor->x, line, "X coordinate is not the same");

	// if(x != coor->x) {
		// sprintf(buffer, "Expected %d, but was %d. X coordinate is not the same", x, coor->x);
		// UNITY_TEST_FAIL(line, buffer);
	// }


	//TEST_ASSERT_EQUAL(y, coor->y);
	//UNITY_TEST_ASSERT_EQUAL_INT(y, coor->y, line, "Y coordinate is not the same");

	// if(y != coor->y) {
		// sprintf(buffer, "Expected %d, but was %d. Y coordinate is not the same", y, coor->y);
		// UNITY_TEST_FAIL(line, buffer);
	// }

	for(i = 0; expectedLine[i] != '\n'; i++)
	{
		if(expectedLine[i] != data->line[i])
		{
			sprintf(buffer, "Expected %c but was %c at position %d. \nExpected %s is not the same with actual %s\n", expectedLine[i], data->line[i], i, expectedLine, data->line);
			UNITY_TEST_FAIL(line, buffer);
		}
	}
}

void assertEqualTLV(char type, char length, char value[], TLV *actual, int line)
{
	int i = 0;
    char msg[64];

	TEST_ASSERT_EQUAL(type, actual->type);
	TEST_ASSERT_EQUAL(length, actual->length);

	for(i = 0; i < length; i++)
	{
        if(value[i] != actual->value[i])
            sprintf(msg, "Data not the same at index %d", i);
		UNITY_TEST_ASSERT_EQUAL_INT(value[i], actual->value[i], line, msg);
		// printf("actual->value[%d]: %2x\n", i, actual->value[i]);
	}
}