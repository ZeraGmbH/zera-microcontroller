#ifndef I2CUTILS_H
#define I2CUTILS_H

#include <QString>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

enum I2cUtilsErrorReturns
{
    I2C_IO_OK = 0,
    I2C_IO_ERR_SETUP = 1,
    I2C_IO_ERR_TRANSACTION = 2
};

int I2CTransfer(QString deviceNode, int i2cadr, i2c_rdwr_ioctl_data* iodata, bool doNotLogTransferNack = false);

bool I2cPing(QString deviceNode, int i2cadr);

#endif // I2CUTILS_H
