#ifndef TLV_Protocol_H
#define TLV_Protocol_H
#include "IntelHex16Operation.h"

// int tlvProtocol();
int openHexFile(FILE *hexFile);
int requestProgrammingMode(TLV *tlv, char receiveByte);
int sendDataCode(FILE *hexFile, TLV *tlv, char *buffer);

#endif // TLV_Protocol_H
