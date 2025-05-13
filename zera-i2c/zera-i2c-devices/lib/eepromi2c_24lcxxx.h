#ifndef EEPROMI2C_24LCXXX_H
#define EEPROMI2C_24LCXXX_H

#include "eepromi2cdeviceinterface.h"
#include "zera-i2c-devices_export.h"
#include <QString>

class ZERA_I2C_DEVICES_EXPORT EepromI2c_24LCxxx : public EepromI2cDeviceInterface
{
public:
    EepromI2c_24LCxxx(QString devNode, short adr, int byteCapacity);
    int WriteData(char* data, ushort count, ushort memAddress) override;
    int ReadData(char* data, ushort count, ushort memAddress) override;
    int Reset() override;

private:
    const QString m_devNodeName;
    const ushort m_i2cAdress;
};

#endif // EEPROMI2C_24LCXXX_H
