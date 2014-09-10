#ifndef TLV_Protocol_H
#define TLV_Protocol_H
#include "IntelHex16Operation.h"

#define COM_PORT        4
#define IntelHexFile    "test/data/LEDBlink.hex"

int tlvProtocol();

int requestProgrammingMode(char receiveByte);
int readHexLineAndCreateIntelHex16Data(FILE *hexFile, IntelHex16Data *data, int *address);
int sendDataCode(TLV *tlv, char receiveByte);
void requestStartRunningMode(void);

#endif // TLV_Protocol_H
