#ifndef I2CFLASHINTERFACE_H
#define I2CFLASHINTERFACE_H

#include <QtGlobal>

class I2cFlashInterface
{
public:
    virtual ~I2cFlashInterface() = default;
    virtual int WriteData(char* data, ushort count, ushort adr) = 0;
    virtual int ReadData(char* data, ushort count, ushort adr) = 0;
    virtual int Reset() = 0;
    virtual int size() = 0;
};

#endif // I2CFLASHINTERFACE_H
