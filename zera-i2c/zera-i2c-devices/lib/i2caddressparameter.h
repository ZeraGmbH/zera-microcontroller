#ifndef I2CADDRESSPARAMETER_H
#define I2CADDRESSPARAMETER_H

#include <QString>

struct I2cAddressParameter {
    QString devNodeFileName;
    ushort i2cAddr;
};

#endif // I2CADDRESSPARAMETER_H
