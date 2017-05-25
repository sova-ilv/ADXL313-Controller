#ifndef USBSERIALAPP_H
#define USBSERIALAPP_H

#include <QString>
#include "../StaticFTDIDriver/i386/FTD2XX.H"

class usbSerialApp
{
public:
    usbSerialApp();

    void initSerialUsb();
    void closeUsbSerial();
    int usb_Send(QString cmd);
    int usb_Receive(char *rxbuf);

    int usb_mipi_write_1byte(int devaddr, unsigned int regaddr, unsigned int wdat);

};

#endif // USBSERIALAPP_H
