#include "IntelHex16Operation.h"
#include "rs232.h"
#include <string.h>
#include <malloc.h>

// char line[1024];

/*
 * To read a line from hex file
 *
 * Input
 *      hexFile     is a pointer to FILE object
 *      buffer      is a string to store a line from hex file
 */
void *readLine(FILE *hexFile, char *buffer)
{
    int i = 0;

    while((buffer[i] = fgetc(hexFile)) != '\n')
    {
        putc(buffer[i], stdout);        // This writes a character to the output
        i++;
    }
    printf("\n");
}

/*
 * To create Intel Hex16 Data
 *
 * Input
 *      line        is a string of a line from the hex file
 */
IntelHex16Data *createIntelHex16Data(char *line)
{
    IntelHex16Data *data = malloc(sizeof(IntelHex16Data));

    data->line = line;

    if(data->line[0] != ':')
        Throw(ERR_NO_COLON);        //throw error if the first character is not colon

    data->index = 0;
}

/*
 * To free the memory allocated by Intel Hex16 data
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 */
IntelHex16Data *deleteIntelHex16Data(IntelHex16Data *data)
{
    if(data != NULL)
        free(data);
}

/*
 * To get a specific byte from Intel Hex16 Data given certain index
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 *      index       is a index of the certain byte to return
 *
 * Return
 *      hex2Int     is a byte of data in integer that converted from hex format
 *      -1          to indicate the index is invalid or no more data left
 */
int getByteFromIntelHex16Data(IntelHex16Data *data, int index)
{
    int i, hex2Int, startPosition;

    startPosition = index - 1;

    i = index + startPosition;

    if(data->line[i] == '\n' || index == 0)
    {
        if(index == 0)
            printf("Invalid index\n");
        else
            printf("No more data left\n");

        return -1;
    }

    sscanf(&(data->line[i]), "%2x", &hex2Int);

    return hex2Int;
}

/*
 * To get the length of the data from the first byte of the hex line
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 *
 * Return
 *      result      is a length of the data in integer format from the first byte of the hex line
 */
int getLengthFromIntelHex16Data(IntelHex16Data *data)
{
    int result;

    result = getByteFromIntelHex16Data(data, 1);

    return result;
}

/*
 * To get the type of the data from the forth byte of the hex line
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 *
 * Return
 *      result      is a type of the data in integer format from the forth byte of the hex line
 */
int getTypeFromIntelHex16Data(IntelHex16Data *data)
{
    int result;

    result = getByteFromIntelHex16Data(data, 4);

    return result;
}

/*
 * To get the address of the data from the second and third byte of the hex line
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 *
 * Return
 *      result      is a address of the data in integer format from the second and third byte of the hex line
 */
int getAddressFromIntelHex16Data(IntelHex16Data *data)
{
    int lowByte, highByte, result;

    lowByte = getByteFromIntelHex16Data(data, 3);
    highByte = getByteFromIntelHex16Data(data, 2);

    result = (highByte << 8) | lowByte;

    return result;
}

/*
 * To verify the check sum value from the hex line
 *
 * Input
 *      data        is a pointer to IntelHex16Data object
 *
 * Return
 *      0           to indicate that there is an error in check sum value
 *      1           to indicate there is no error in check sum value
 */
int verifyCheckSumOfIntelHex16Data(IntelHex16Data *data)
{
    int i, result = 0, checkSum = 0;

    for(i = 1; result != -1; i++)
    {
        result = getByteFromIntelHex16Data(data, i);

        if(result != -1)
            checkSum += result;
    }

    checkSum = checkSum & 0x0ff;

    if(checkSum == 0)
        return 1;

    return 0;
}

/*
 * To get the LSB byte from the address and the shift the address to the right
 *
 * Input
 *      address     is the starting address of the hex line
 *
 * Return
 *      byte        LSB byte from the address
 */
int getLSByteAndShiftRight(int long *address)
{
    int byte;

    byte = *address & 0x000000ff;

    *address = *address >> 8;

    return byte;
}

/*
 * To create a TLV program message from IntelHex16Data
 *
 * Input
 *      data            is a pointer to IntelHex16Data object
 *      addressHigh     is a upper address of the starting address
 *
 * Return
 *      tlvMessage      is a pointer to TLV object
 */
TLV *createProgramMessage(IntelHex16Data *data, int addressHigh)
{
    int length, addressLow, j;
    int long address32bit;

    TLV *tlvMessage = malloc(sizeof(TLV) + sizeof(char) * (addressAndCS + length));
    sscanf(&(data->line[1]), "%2x", &length);
    tlvMessage->type = PROGRAM_MSG;
    tlvMessage->length = length + addressAndCS;

    if(!verifyCheckSumOfIntelHex16Data(data))
        Throw(ERR_WRONG_CHECKSUM);

    addressLow = getAddressFromIntelHex16Data(data);
    address32bit = (addressHigh << 16) | addressLow;

    for(j = 0; j < 4; j++)
    {
        tlvMessage->value[j] = getLSByteAndShiftRight(&address32bit);
    }

    for(j = 4; j < (length + 5); j++)
    {
        tlvMessage->value[j] = getByteFromIntelHex16Data(data, j + 1);
    }

    tlvMessage->value[j] = 0;

    return tlvMessage;
}

/*
 * To create a TLV Start Running Message for PIC18 module to run the target
 *
 * Return
 *      tlvMessage      is a pointer to TLV object
 */
TLV *createStartRunningMessage()
{
    TLV *tlvMessage = malloc(sizeof(TLV));
    tlvMessage->type = START_RUNNING;

    return tlvMessage;
}

TLV *createInquireTargetAvailability()
{
    TLV *tlvMessage = malloc(sizeof(TLV));
    tlvMessage->type = TARGET_AVAILABLITY;

    return tlvMessage;
}

/*
 * To create a TLV Programming Mode Message for PIC18 module to reset the target
 *
 * Return
 *      tlvMessage      is a pointer to TLV object
 */
TLV *createProgrammingMode()
{
    TLV *tlvMessage = malloc(sizeof(TLV));
    tlvMessage->type = PROGRAMMING_MODE;

    return tlvMessage;
}

/*
 * To free the memory allocated by tlv
 *
 * Input
 *      tlv     is a pointer to TLV object
 */
TLV *deleteTLV(TLV *tlv)
{
    if(tlv != NULL && tlv->type == PROGRAM_MSG)
    {
        free(tlv->value);
        free(tlv);
    }
    else
        free(tlv);
}

/*
 * To send the tlv's length, type and value through serial transmit
 *
 * Input
 *      tlv     is a pointer to TLV object
 */
void sendTLV(TLV *tlv)
{
    int i;

    RS232_SendByte(COM_PORT, tlv->type);

    RS232_SendByte(COM_PORT, tlv->length);

    for(i = 0; i < tlv->length; i++)
        RS232_SendByte(COM_PORT, tlv->value[i]);
}