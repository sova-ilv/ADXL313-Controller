#include "adxl313.h"
#include <qdebug.h>

ADXL313::ADXL313()
{
    //int iarray[3];
    //readInfoRegisters(iarray);
    //qDebug() << "I got - 0" << iarray[0];
    //qDebug() << "I got - 1" << iarray[1];
    //qDebug() << "I got - 2" << iarray[2];

}

void ADXL313::readInfoRegisters(int *infoArray)
{
    //Read through the STM32F4

    infoArray[0] = 0x21;
    infoArray[1] = 0xff;
    infoArray[2] = 0x45;
}

int ADXL313::readByteAddr(int addr)
{

    return 45;
}

int ADXL313::writeByteAddr(int addr, int dat)
{
    return 0;
}

