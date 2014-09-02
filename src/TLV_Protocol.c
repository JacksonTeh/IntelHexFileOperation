#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "rs232.h"
#include <stdio.h>

#define COM_PORT 2
#define IntelHexFile "LEDBlink.hex"

int openHexFile(FILE *hexFile)
{
	if(hexFile == NULL)
	{
		printf("Error: cannot open the file %s\n", IntelHexFile);
		return 0;	// Terminate the program immediately
	}
	
	return 1;
}

int requestProgrammingMode(TLV *tlv, char receiveByte)
{
	// do
	// {
		RS232_SendByte(COM_PORT, tlv->type);
		Sleep(100);
		// Sleep(100);
		RS232_PollComport(COM_PORT, &receiveByte, 1);
	// }while(receiveByte != ACK);

	if(receiveByte != ACK)
		return 0;

	return 1;
}

int sendDataCode(FILE *hexFile, TLV *tlv, char *buffer)
{
	readLine(hexFile, buffer);
	
	data = createIntelHex16Data(buffer);
}

// int tlvProtocol()
// {
	// int address, dataHigh, dataLow, i = 0;
	// char buffer[1024], receiveByte = ACK, getByte;
	// FILE *hexFile;
	// IntelHex16Data *data;
	// TLV *tlvMessage;

	// RS232_OpenComport(COM_PORT, 9600);

// /* 	data = createIntelHex16Data(buffer);
	// address = 0x0000;

	// tlvMessage = createProgramMessage(data, address);

	// sendTLV(tlvMessage);

	// deleteIntelHex16Data(data);
	// deleteTLV(tlvMessage); */

	// /* RS232_SendByte(COM_PORT, 0x55);
	// Sleep(100);
	// RS232_PollComport(COM_PORT, &receiveByte, 1);

	// printf("ACK: %d\n", receiveByte); */

 	// do{
		// readLine(hexFile, buffer);
		// data = createIntelHex16Data(buffer);

		// getByte = getByteFromIntelHex16Data(data, 4);

		// if(getByte == 4)
		// {
			// dataHigh = getByteFromIntelHex16Data(data, 5);
			// dataLow = getByteFromIntelHex16Data(data, 6);
			// address = (dataHigh << 8) | dataLow;
			// deleteIntelHex16Data(data);
		// }
		// else if(getByte != 1)
		// {
			// tlvMessage = createProgramMessage(data, address);

			// sendTLV(tlvMessage);

			// deleteTLV(tlvMessage);
		// }

		// deleteIntelHex16Data(data);
		//i++;
	// }while(getByte != 1/* i<2 */);

	// tlvMessage = createProgrammingMode();

	// do{
		// RS232_SendByte(COM_PORT, tlvMessage->type);
		// Sleep(100);
		// RS232_PollComport(COM_PORT, &receiveByte, 1);
	// }while(receiveByte == NACK);

	// deleteTLV(tlvMessage);

// /* 	RS232_SendByte(COM_PORT, 0x01);
	// RS232_SendByte(COM_PORT, 0x0b);
	// RS232_SendByte(COM_PORT, 0x04);
	// RS232_SendByte(COM_PORT, 0x00);
	// RS232_SendByte(COM_PORT, 0x00);
	// RS232_SendByte(COM_PORT, 0x00);
	// RS232_SendByte(COM_PORT, 0x02);
	// RS232_SendByte(COM_PORT, 0x0e);
	// RS232_SendByte(COM_PORT, 0x45);
	// RS232_SendByte(COM_PORT, 0x18);
	// RS232_SendByte(COM_PORT, 0x73);
	// RS232_SendByte(COM_PORT, 0x27);
	// RS232_SendByte(COM_PORT, 0xe1); */

	// RS232_CloseComport(COM_PORT);

	// fclose(hexFile);

	// printf("Finish\n");

	// return 1;
// }

