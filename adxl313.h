#ifndef ADXL313_H
#define ADXL313_H


class ADXL313
{
public:
    ADXL313();

    void readInfoRegisters(int *infoArray);
    int readByteAddr(int addr);
    int writeByteAddr(int addr, int dat);
};

#endif // ADXL313_H
