#include "i2ceeprom_p.h"

cI2CEEPromPrivate::cI2CEEPromPrivate(QString dNode, ushort i2cAdress) :
    m_devNodeName(dNode),
    m_i2cAdress(i2cAdress)
{
}
