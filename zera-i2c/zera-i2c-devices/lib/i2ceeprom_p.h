#ifndef I2CEEPROM_P_H
#define I2CEEPROM_P_H

#include <QString>
#include <QTimer>

class cI2CEEPromPrivate
{
public:
    cI2CEEPromPrivate(QString dNode, ushort i2cAdress);
    cI2CEEPromPrivate(){};
    virtual ~cI2CEEPromPrivate(){};

    virtual int WriteData(char* data, ushort count, ushort adr) = 0;
    virtual int ReadData(char* data, ushort count, ushort adr) = 0;
    virtual int Reset() = 0;
    virtual int size() = 0;
protected:
    QString m_devNodeName;
    ushort m_i2cAdress;
};

#endif // I2CEEPROM_P_H
