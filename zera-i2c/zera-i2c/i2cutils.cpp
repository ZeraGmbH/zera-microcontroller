#include "i2cutils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QByteArray>
#include <errno.h>
#include <linux/i2c.h>

int I2CTransfer(QString deviceNode, int i2cadr, i2c_rdwr_ioctl_data* iodata, bool doNotLogTransferNack)
{
    int fd = open(deviceNode.toLatin1().constData(), O_RDWR);
    if (fd < 0) {
        qWarning("Error opening i2c device %s / 0x%02X Error message: %s",
                 qPrintable(deviceNode), i2cadr, strerror(errno));
        return I2C_IO_ERR_SETUP;
    }
    if (ioctl(fd, I2C_RETRIES, 0) < 0) {
        close(fd);
        qWarning("Error setting retries of i2c device %s / 0x%02X Error message: %s",
                 qPrintable(deviceNode), i2cadr, strerror(errno));
        return I2C_IO_ERR_SETUP;
    }
    if (ioctl(fd, I2C_TIMEOUT, 500) < 0) {
        close(fd);
        qWarning("Error setting timeout of i2c device %s / 0x%02X Error message: %s",
                 qPrintable(deviceNode), i2cadr, strerror(errno));
        return I2C_IO_ERR_SETUP;
    }
    if (ioctl(fd, I2C_RDWR, iodata) < 0) {
        close(fd);
        if(!doNotLogTransferNack)
            qWarning("Error read/write of i2c device %s / 0x%02X Error message: %s",
                     qPrintable(deviceNode), i2cadr, strerror(errno));
        return I2C_IO_ERR_TRANSACTION;
    }
    close(fd);
    return I2C_IO_OK;
}

// stolen from https://github.com/mozilla-b2g/i2c-tools
__s32 i2c_smbus_access(int file, char read_write, __u8 command,
                       int size, union i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args;
    __s32 err;

    args.read_write = read_write;
    args.command = command;
    args.size = size;
    args.data = data;

    err = ioctl(file, I2C_SMBUS, &args);
    if (err == -1)
        err = -errno;
    return err;
}

__s32 i2c_smbus_read_byte(int file)
{
    union i2c_smbus_data data;
    int err;

    err = i2c_smbus_access(file, I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data);
    if (err < 0)
        return err;

    return 0x0FF & data.byte;
}

bool I2cPing(QString deviceNode, int i2cadr)
{
    bool bDevConnected = false;
    int file = open(deviceNode.toLatin1().data(), O_RDWR);
    if(file >=0) {
        unsigned long funcs;
        if (ioctl(file, I2C_FUNCS, &funcs) >= 0) {
            if (ioctl(file, I2C_SLAVE, i2cadr) >= 0) {
                bDevConnected = i2c_smbus_read_byte(file) >= 0;
            }
        }
        close(file);
    }
    return bDevConnected;
}
