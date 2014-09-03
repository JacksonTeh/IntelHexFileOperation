#ifndef TLV_Protocol_H
#define TLV_Protocol_H
#include "IntelHex16Operation.h"

int tlvProtocol();

int requestProgrammingMode(char receiveByte);
int readHexLineAndCreateIntelHex16Data(FILE *hexFile, IntelHex16Data *data, int *address);
int sendDataCode(TLV *tlv, char receiveByte);
void requestStartRunningMode(void);

#endif // TLV_Protocol_H
