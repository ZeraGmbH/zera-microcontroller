#ifndef F24LC256_P_H
#define F24LC256_P_H

#include "i2cflashinterface.h"
#include <QString>

class cF24LC256Private: public I2cFlashInterface
{
public:
    cF24LC256Private(QString devNode, short adr);
    int WriteData(char* data, ushort count, ushort memAddress) override;
    int ReadData(char* data, ushort count, ushort memAddress) override;
    int Reset() override;
    int size() override;

private:
    QString getDeviceNodeName();
    ushort getI2cAddress();

    QString m_devNodeName;
    ushort m_i2cAdress;
};

#endif // F24LC256_P_H
