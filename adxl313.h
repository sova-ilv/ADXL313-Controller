#ifndef ADXL313_H
#define ADXL313_H


class ADXL313
{
public:
    ADXL313();

    void readInfoRegisters(int *infoArray);

    ADXL313 myAccel;
};

#endif // ADXL313_H
