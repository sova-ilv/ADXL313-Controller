#include <QString>
#include <iostream>
#include <QMessageBox>
#include "usbserialapp.h"

#define MAX_DEVICES 4
FT_STATUS ftstatus;
HRESULT status;
FT_HANDLE FTDIHandle = 0;
DWORD BytesWritten,  EventDWord, TxBytes, RxBytes;
char usb_Serial[100];

usbSerialApp::usbSerialApp()
{

}

void usbSerialApp::initSerialUsb()
{
    char *BufPtrs[MAX_DEVICES + 1];		// pointer to array of pointers
    char Buffer[MAX_DEVICES][64];		// buffer for description of devices
    unsigned long numDevs;
    int i;

         // initialize the array of pointers
           for (i=0; i<MAX_DEVICES; i++) BufPtrs[i] = Buffer[i];
                BufPtrs[MAX_DEVICES] = NULL;      // last entry should be NULL
                //

           status = FT_ListDevices(BufPtrs, &numDevs, FT_LIST_ALL|FT_OPEN_BY_SERIAL_NUMBER);
                //ftstatus = FT_CreateDeviceInfoList(&numDevs);
           strcpy (usb_Serial, Buffer[0]); //The index of Buffer is typically vcp seq number or the index of how many FTDI devices connected
                                               //NOTE: this should be on ini file

           ftstatus = FT_OpenEx(usb_Serial, FT_OPEN_BY_SERIAL_NUMBER,&FTDIHandle);
           if (FTDIHandle) {
                    ftstatus = FT_SetBaudRate(FTDIHandle, 460800 );
                    ftstatus = FT_SetDataCharacteristics(FTDIHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
                    FT_SetTimeouts(FTDIHandle,500,5);

                    ftstatus = FT_SetUSBParameters(FTDIHandle, 640,640); //default is is 4096 bytes, (way too high)

                    QMessageBox::information(0, "info", "now connected to usb FW.");
                }
           else
                {
                    QMessageBox::critical(0, "Error", "USB device was not found!");
           }
}

void usbSerialApp::closeUsbSerial()
{
    FT_Close(FTDIHandle);
}

int usbSerialApp::usb_Send(QString cmd)
{
    QByteArray array = cmd.toLocal8Bit();
    char* buffer = array.data();

            int len = strlen(buffer);
            ftstatus = FT_Write(FTDIHandle, buffer, len, &BytesWritten);
            if (ftstatus != FT_OK) return -1;
            return 0;
}

int usbSerialApp::usb_Receive(char *rxbuf)
{
    char tempbuf[20];

    DWORD numberOfCharactersToRead = 20; //256;
    DWORD bytesWrittenOrRead;

    rxbuf[0]='\0';
    ftstatus = FT_Read(FTDIHandle, tempbuf, (DWORD)numberOfCharactersToRead, &bytesWrittenOrRead);
    strcpy(rxbuf, tempbuf);
    return 0;
}

int usbSerialApp::usb_mipi_write_1byte(int devaddr, unsigned int regaddr, unsigned int wdat)
{
    char read_com[256];
    int ret=0;

           read_com[0] = '\0';
           sprintf(read_com, "w1 %x %.2x %.2x\r", devaddr, regaddr, wdat & 0xFF);

           ret = usb_Send(read_com);
           if (ret != FT_OK) return -1;

        Sleep(30);
        return ret;
}
