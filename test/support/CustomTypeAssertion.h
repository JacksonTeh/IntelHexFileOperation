#ifndef CustomTypeAssertion_H
#define CustomTypeAssertion_H

#include "IntelHex16Operation.h"
#include <stdio.h>

#define TEST_ASSERT_EQUAL_ReadLine(expectedLine, actualLine)	\
			   assertEqualReadLine(expectedLine,				\
								   actualLine,					\
								   __LINE__						\
								  );

#define TEST_ASSERT_EQUAL_TLV(type, length, value, actual)		\
			   assertEqualTLV(type,								\
							  length,							\
							  value,							\
							  actual,							\
							  __LINE__							\
							  );

#define TEST_OPEN_FILE(filename, errorMsg)             \
               testOpenFile(filename, errorMsg, __LINE__);

void assertEqualReadLine(char *expectedLine, IntelHex16Data *data, int line);
void assertEqualTLV(char type, char length, char value[], TLV *actual, int line);
FILE *testOpenFile(char *filename, char *errorMsg, int line);

#endif // CustomTypeAssertion_H