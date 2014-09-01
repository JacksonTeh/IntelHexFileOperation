#ifndef CustomTypeAssertion_H
#define CustomTypeAssertion_H

#include "IntelHex16Operation.h"

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

void assertEqualReadLine(char *expectedLine, IntelHex16Data *data, int line);
void assertEqualTLV(char type, char length, char value[], TLV *actual, int line);
// void assertEqualsendTLV();

#endif // CustomTypeAssertion_H