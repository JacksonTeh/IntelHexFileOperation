#ifndef TLV_Protocol_H
#define TLV_Protocol_H
#include "IntelHex16Operation.h"

#define IntelHexFile    "test/data/LEDBlink.hex"

int requestProgrammingMode(char receiveByte);
int readHexLineAndCreateIntelHex16Data(FILE *hexFile, IntelHex16Data **data, int *address);
int sendDataCode(IntelHex16Data *data, int address, char receiveByte);
void requestStartRunningMode(void);

#endif // TLV_Protocol_H
