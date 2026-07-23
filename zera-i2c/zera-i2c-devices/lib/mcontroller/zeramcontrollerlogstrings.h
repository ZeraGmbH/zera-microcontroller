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

    static QString getErrorMaskText(quint32 errorFlags, bool bootCmd);

private:
    static void fillTextHashes();
    static void appendMasterErrorFlags(QHash<quint32, QString>& errorFlagsText);

    static QHash<quint32, QString> m_errorFlagsText;
    static QHash<quint32, QString> m_errorFlagsBootText;
};

#endif // ZERAMCONTROLLERLOGSTRINGS_H
