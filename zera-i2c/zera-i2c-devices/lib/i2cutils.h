#ifndef I2CUTILS_H
#define I2CUTILS_H

#include <QString>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

enum I2cUtilsErrorReturns
{
    I2C_IO_OK,
    I2C_IO_ERR_SETUP,
    I2C_IO_ERR_TRANSACTION
};

I2cUtilsErrorReturns I2CTransfer(const QString &deviceNode, int i2cadr, i2c_rdwr_ioctl_data* iodata, bool doNotLogTransferErrors = false);
int getLastI2cTransferErrorNo();
QString getLastI2cTransferErrorStr();
QString getLastI2cTransferErrorStep(I2cUtilsErrorReturns step);

bool I2cPing(const QString &deviceNode, int i2cadr);

#endif // I2CUTILS_H
