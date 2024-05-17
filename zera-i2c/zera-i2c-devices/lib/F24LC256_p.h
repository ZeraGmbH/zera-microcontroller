#ifndef F24LC256_P_H
#define F24LC256_P_H

#include "i2ceeprom_p.h"

class cF24LC256Private: public cI2CEEPromPrivate
{
public:
    cF24LC256Private(QString devNode, short adr);
    virtual ~cF24LC256Private() = default;
    int WriteData(char* data, ushort count, ushort memAddress) override;
    int ReadData(char* data, ushort count, ushort memAddress) override;
    int Reset() override;
    int size() override;
};

#endif // F24LC256_P_H
