#ifndef IntelHex16Operation_H
#define IntelHex16Operation_H
#include <stdio.h>
#include <stdlib.h>

#define COM_PORT        4
#define addressAndCS    5

typedef enum {ERR_NO_ERROR, ERR_NO_COLON, ERR_WRONG_CHECKSUM} ErrorLine;
typedef enum {NOTHING, PROGRAM_MSG, START_RUNNING, TARGET_AVAILABLITY, ACK, NACK, PROGRAMMING_MODE} TLV_Message;

typedef struct
{
    char type;
    char length;
    char value[0];
} TLV;

typedef struct
{
    char *line;
    int index;
} IntelHex16Data;

void *readLine(FILE *hexFile, char *buffer);
IntelHex16Data *createIntelHex16Data(char *line);
IntelHex16Data *deleteIntelHex16Data(IntelHex16Data *data);
int getByteFromIntelHex16Data(IntelHex16Data *data, int index);
int getLengthFromIntelHex16Data(IntelHex16Data *data);
int getTypeFromIntelHex16Data(IntelHex16Data *data);
int getAddressFromIntelHex16Data(IntelHex16Data *data);
int verifyCheckSumOfIntelHex16Data(IntelHex16Data *data);
int getLSByteAndShiftRight(int long *address);

TLV *createProgramMessage(IntelHex16Data *data, int addressHigh);
TLV *createStartRunningMessage();
TLV *createInquireTargetAvailability();
TLV *createProgrammingMode();
TLV *deleteTLV(TLV *tlv);

void sendTLV(TLV *tlv);

#endif // IntelHex16Operation_H
