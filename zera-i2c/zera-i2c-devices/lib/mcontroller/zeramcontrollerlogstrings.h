#ifndef ZERAMCONTROLLERLOGSTRINGS_H
#define ZERAMCONTROLLERLOGSTRINGS_H

#include "protocol_zera_hard.h"
#include "protocol_zera_bootloader.h"
#include <QString>

class ZeraMControllerLogStrings
{
public:
    static QString getHexParam(hw_cmd *hc);
    static QString getHexParam(bl_cmd *blc);
    static QString getHexData(quint8 *data, quint16 dataAndCrcLen);
};

#endif // ZERAMCONTROLLERLOGSTRINGS_H
