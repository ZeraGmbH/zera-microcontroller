#ifndef F24LC256_H
#define F24LC256_H

#include "i2cflashinterface.h"
#include "i2ceeprom_p.h"
#include "zera-i2c-devices_export.h"

class cF24LC256Private;

class ZERA_I2C_DEVICES_EXPORT cF24LC256 : public cI2CEEPromPrivate, public I2cFlashInterface
{
public:
    cF24LC256(QString devNode, short adr);
    virtual ~cF24LC256();
    int WriteData(char* data, ushort count, ushort adr) override;
    int ReadData(char* data, ushort count, ushort adr) override;
    int Reset() override;
    int size() override;
private:
    cF24LC256Private* d_ptr;
};

#endif // F24LC256_H
