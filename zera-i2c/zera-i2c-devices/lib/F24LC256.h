#ifndef F24LC256_H
#define F24LC256_H

#include "i2cflashinterface.h"
#include "zera-i2c-devices_export.h"
#include <QString>

class ZERA_I2C_DEVICES_EXPORT cF24LC256 : public I2cFlashInterface
{
public:
    cF24LC256(QString devNode, short adr);
    int WriteData(char* data, ushort count, ushort memAddress) override;
    int ReadData(char* data, ushort count, ushort memAddress) override;
    int Reset() override;
    int size() override;

private:
    const QString m_devNodeName;
    const ushort m_i2cAdress;
};

#endif // F24LC256_H
