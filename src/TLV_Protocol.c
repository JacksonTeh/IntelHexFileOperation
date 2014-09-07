#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "rs232.h"
#include <stdio.h>

#define COM_PORT 4
#define IntelHexFile "test/data/LEDBlink.hex"

/*
 * To request Programming Mode from the PIC module
 *
 * Input
 *		receiveByte		is the byte receive through RS232
 *
 * Return
 *		0		to indicate Programming Mode is unable to request
 *		1		to indicate Programming Mode is able to request
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
 *		hexFile		is a pointer to FILE object
 *		data		is a pointer to IntelHex16Data object
 *		address		is a pointer to two high byte of extented address
 *
 * Return
 *		0		to indicate the end of the hex line
 *		1		to indicate there still some hex line left
 *		-1		to indicate nothing to return
 */
int readHexLineAndCreateIntelHex16Data(FILE *hexFile, IntelHex16Data *data, int *address)
{
	char buffer[1024], getType;
	int dataHigh, dataLow;

	readLine(hexFile, buffer);

	data = createIntelHex16Data(buffer);

	getType = getByteFromIntelHex16Data(data, 4);

	if(getType == 4)
	{
		dataHigh = getByteFromIntelHex16Data(data, 5);
		dataLow = getByteFromIntelHex16Data(data, 6);
		*address = (dataHigh << 8) | dataLow;
		deleteIntelHex16Data(data);
		return -1;
	}
	else if(getType == 1)
	{
		deleteIntelHex16Data(data);
		return 0;
	}
	else
		return 1;
}

/*
 * To send data code to the PIC module to program
 *
 * Input
 *		tlv				is a pointer to TLV object
 *		receiveByte		is the byte receive through RS232
 *
 * Return
 *		0		to indicate NACK is receive from the PIC module
 *		1		to indicate the program is able to flash
 */
int sendDataCode(TLV *tlv, char receiveByte)
{
	sendTLV(tlv);
	Sleep(100);

	RS232_PollComport(COM_PORT, &receiveByte, 1);

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

int tlvProtocol()
{
	int address = 0x0000, programmingModeStatus, sendStatus, result, i = 0;
	char receiveByte;
	FILE *hexFile;
	IntelHex16Data *data;
	TLV *tlvMessage;

	hexFile = fopen(IntelHexFile, "r");

	if(hexFile == NULL)
	{
		printf("error: cannot open the file LEDBlink.hex");
		return 0;	// Terminate the program immediately if file unable to open
	}

	RS232_OpenComport(COM_PORT, 9600);

	receiveByte = NACK;
	do{
		if(i == 3)
			return 0;	// Terminate the program immediately if the programming mode is unable to set

		programmingModeStatus = requestProgrammingMode(receiveByte);
		i++;
	}while(!programmingModeStatus);		//repeat request again if the ACK is not receive

	receiveByte = ACK;
	do{
		result = readHexLineAndCreateIntelHex16Data(hexFile, data, &address);

		if(result == 1)
		{
			tlvMessage = createProgrammingMode(data, address);

			do{
				sendStatus = sendDataCode(tlvMessage, receiveByte);
			}while(!sendStatus);		//repeat sending the same tlv if the ACK is not receive

			deleteIntelHex16Data(data);
			deleteTLV(tlvMessage);
		}
	}while(result == 0);

	requestStartRunningMode();

	RS232_CloseComport(COM_PORT);

	fclose(hexFile);
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