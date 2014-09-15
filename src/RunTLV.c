#include "RunTLV.h"
#include "TLV_Protocol.h"
#include "IntelHex16Operation.h"
#include "rs232.h"
#include <stdio.h>

int tlvProtocol()
{
    int address = 0x0000, programmingModeStatus, sendStatus, result, i = 0;
    char receiveByte;
    FILE *hexFile;
    IntelHex16Data *data;

    hexFile = fopen(IntelHexFile, "r");

    if(hexFile == NULL)
    {
        printf("error: cannot open the file LEDBlink.hex");
        return 0;       // Terminate the program immediately if file unable to open
    }

    RS232_OpenComport(COM_PORT, 9600);

    /* receiveByte = NACK;
     do{
        if(i == 3)
            return 0;   // Terminate the program immediately if the programming mode is unable to set

        programmingModeStatus = requestProgrammingMode(receiveByte);
        i++;
    }while(!programmingModeStatus); */     //repeat request again if the ACK is not receive

    receiveByte = ACK;
/*     do{
        result = readHexLineAndCreateIntelHex16Data(hexFile, &data, &address);

        if(result == 1)
        {
            do{
                sendStatus = sendDataCode(data, address, receiveByte);
            }while(!sendStatus);        //repeat sending the same tlv if the ACK is not receive
            deleteIntelHex16Data(data);
        }

    }while(result != 0); */

    result = readHexLineAndCreateIntelHex16Data(hexFile, &data, &address);
    result = readHexLineAndCreateIntelHex16Data(hexFile, &data, &address);
    printf("data: %p\n", data);
    sendStatus = sendDataCode(data, address, receiveByte);
    deleteIntelHex16Data(data);

/*    requestStartRunningMode();*/

    RS232_CloseComport(COM_PORT);

    fclose(hexFile);

    return 1;
}