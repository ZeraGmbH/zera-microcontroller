#include "zeramcontrollerlogstrings.h"

QString ZeraMControllerLogStrings::getHexParam(hw_cmd *hc)
{
    QString i2cHexParam;
    if (hc->par)
        for(int iByte=0; iByte<hc->plen; iByte++)
            i2cHexParam += QString("0x%1 ").arg(hc->par[iByte], 2, 16, QLatin1Char('0'));
    return i2cHexParam;
}

QString ZeraMControllerLogStrings::getHexParam(bl_cmd *blc)
{
    QString i2cHexParam;
    if (blc->par)
        for(int iByte=0; iByte<blc->paramOrRequestedLen; iByte++)
            i2cHexParam += QString("0x%1 ").arg(blc->par[iByte], 2, 16, QLatin1Char('0'));
    return i2cHexParam;
}

QString ZeraMControllerLogStrings::getHexData(quint8 *data, quint16 dataAndCrcLen)
{
    QString i2cHexData;
    for(quint16 iByte=0; iByte<dataAndCrcLen; iByte++) {
        i2cHexData += QString("0x%1 ").arg(data[iByte], 2, 16, QLatin1Char('0'));
    }
    return i2cHexData;
}
