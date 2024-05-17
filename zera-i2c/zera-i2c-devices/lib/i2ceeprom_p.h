#ifndef I2CEEPROM_P_H
#define I2CEEPROM_P_H

#include <QString>
#include <QTimer>

class cI2CEEPromPrivate
{
public:
    cI2CEEPromPrivate(QString dNode, ushort adr);
    cI2CEEPromPrivate(){};
    virtual ~cI2CEEPromPrivate(){};

    virtual int WriteData(char* data, ushort count, ushort adr) = 0;
    virtual int ReadData(char* data, ushort count, ushort adr) = 0;
    virtual int Reset() = 0;
    virtual int size() = 0;
protected:
    QString DevNode;
    ushort I2CAdress;
};

#endif // I2CEEPROM_P_H
