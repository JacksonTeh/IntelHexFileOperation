#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "rs232.h"
#include <stdio.h>

/*
 * To request Programming Mode from the PIC module
 *
 * Input
 *      receiveByte     is the byte receive through RS232
 *
 * Return
 *      0       to indicate Programming Mode is unable to request
 *      1       to indicate Programming Mode is able to request
 */
int requestProgrammingMode(char receiveByte)
{
    TLV *tlvMessage = createProgrammingMode();

    RS232_SendByte(COM_PORT, tlvMessage->type);

    Sleep(100);

    RS232_PollComport(COM_PORT, &receiveByte, 1);

    deleteTLV(tlvMessage);

    if(receiveByte != ACK)
        return 0;

    return 1;
}

/*
 * To read a hex line and then create Intel Hex16 Data
 *
 * Input
 *      hexFile     is a pointer to FILE object
 *      data        is a pointer to IntelHex16Data object
 *      address     is a pointer to two high byte of extented address
 *
 * Return
 *      0       to indicate the end of the hex line
 *      1       to indicate there still some hex line left
 *      -1      to indicate nothing to return
 */
int readHexLineAndCreateIntelHex16Data(FILE *hexFile, IntelHex16Data **data, int *address)
{
    char buffer[1024], getType;
    int dataHigh, dataLow;

    readLine(hexFile, buffer);

    *data = createIntelHex16Data(buffer);

    getType = getByteFromIntelHex16Data(*data, 4);

    if(getType == 4)
    {
        dataHigh = getByteFromIntelHex16Data(*data, 5);
        dataLow = getByteFromIntelHex16Data(*data, 6);
        *address = (dataHigh << 8) | dataLow;
        deleteIntelHex16Data(*data);
        return -1;
    }
    else if(getType == 1)
    {
        deleteIntelHex16Data(*data);
        return 0;
    }
    else
        return 1;
}

/*
 * To send data code to the PIC module to program
 *
 * Input
 *      tlv             is a pointer to TLV object
 *      receiveByte     is the byte receive through RS232
 *
 * Return
 *      0       to indicate NACK is receive from the PIC module
 *      1       to indicate the program is able to flash
 */
int sendDataCode(IntelHex16Data *data, int address, char receiveByte)
{
    TLV *tlvMessage = createProgramMessage(data, address);
    printf("&data: %p\n", data);

    sendTLV(tlvMessage);
    Sleep(100);

    RS232_PollComport(COM_PORT, &receiveByte, 1);

    deleteTLV(tlvMessage);

    if(receiveByte == ERR_WRONG_TYPE)
        Throw(ERR_WRONG_TYPE);

    if(receiveByte == ERR_WRONG_CHECKSUM)
        Throw(ERR_WRONG_CHECKSUM);

    if(receiveByte != ACK)
        return 0;

    return 1;
}

/*
 * To request Start Running Mode from the PIC module
 */
void requestStartRunningMode(void)
{
    TLV *tlvMessage = createStartRunningMessage();

    RS232_SendByte(COM_PORT, tlvMessage->type);

    deleteTLV(tlvMessage);
}

/* 	RS232_SendByte(COM_PORT, 0x01);
	RS232_SendByte(COM_PORT, 0x0b);
	RS232_SendByte(COM_PORT, 0x04);
	RS232_SendByte(COM_PORT, 0x00);
	RS232_SendByte(COM_PORT, 0x00);
	RS232_SendByte(COM_PORT, 0x00);
	RS232_SendByte(COM_PORT, 0x02);
	RS232_SendByte(COM_PORT, 0x0e);
	RS232_SendByte(COM_PORT, 0x45);
	RS232_SendByte(COM_PORT, 0x18);
	RS232_SendByte(COM_PORT, 0x73);
	RS232_SendByte(COM_PORT, 0x27);
	RS232_SendByte(COM_PORT, 0xe1); */