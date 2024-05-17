#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <QString>
#include "i2cutils.h"
#include "i2ceeprom_p.h"
#include "F24LC256_p.h"

cF24LC256Private::cF24LC256Private(QString devNode, short adr)
    : cI2CEEPromPrivate(devNode, adr)
{
}

int cF24LC256Private::WriteData(char* data, ushort count, ushort memAddress)
{
    uchar outpBuf[66]; // 2 address bytes, max 64 byte data
    struct i2c_msg Msgs = {.addr = m_i2cAdress, .flags = I2C_M_RD, .len =  5, .buf = outpBuf }; // 1 message
    struct i2c_rdwr_ioctl_data EEPromData = {.msgs = &(Msgs), .nmsgs = 1 };
    int toWrite = count;

    if ( I2CTransfer(m_devNodeName, m_i2cAdress, &EEPromData) )
        return 0; // we couldn't write any data

    Msgs.flags = 0; // switch to write direction
    char* mydata = data;
    while (toWrite && memAddress < size()) {
        outpBuf[0] = (memAddress >> 8) & 0xff;
        outpBuf[1] = memAddress & 0xff;

        int pl = 64 - (memAddress & 0x3f); // how many bytes for the actual page
        int l = (toWrite > pl) ? pl : toWrite; // so we decide how many bytes to write now
        memcpy((void*)&outpBuf[2],(void*)mydata,l);
        mydata += l;
        Msgs.len = l+2; // set length for i2c driver
        int r;
        for (int i = 0; i < 100; i++) {
            r = I2CTransfer(m_devNodeName, m_i2cAdress, &EEPromData, true);
            if(r == I2C_IO_OK)
                break;
            // NACKs are fine and signalling that chip is still busy with previous page
            // see ACKNOWLEDGE POLLING in
            // https://ww1.microchip.com/downloads/en/devicedoc/21203r.pdf
            else if(r == I2C_IO_ERR_TRANSACTION)
                usleep(100);
            else
                break;
        }
        if(r)
            break; // // device node ok , but eeprom is busy or i2c nak because write protection
        memAddress += l; // set adress where to go on
        toWrite -= l; // actualize byte to write
    }
    return(count - toWrite);
}

int cF24LC256Private::Reset()
{
    char freshBuff[size()];
    for(int i=0; i<size(); ++i)
        freshBuff[i] = 0xFF;
    return WriteData(freshBuff, size(), 0);
}

#define blockReadLen 4096

int cF24LC256Private::ReadData(char* data, ushort n, ushort memAddress)
{
    uchar outpBuf[2];
    uchar inpBuf[blockReadLen]; // the max. blocklength
    struct i2c_msg Msgs[2] = { {.addr = m_i2cAdress, .flags = 0,.len = 2,.buf = &(outpBuf[0])}, // 2 messages (tagged format )
                               {.addr = m_i2cAdress, .flags = (I2C_M_RD+I2C_M_NOSTART), .len = blockReadLen, .buf = &(inpBuf[0])} };
    struct i2c_rdwr_ioctl_data EEPromData = {.msgs = &(Msgs[0]), .nmsgs = 2 };

    ushort toRead = n;
    while (toRead)
    {
        ushort l = (toRead > blockReadLen) ? blockReadLen : toRead;
        outpBuf[0]=(memAddress >> 8) & 0xff; outpBuf[1]=memAddress & 0xff; // we set the adress for the next transfer
        Msgs[1].len = l; // and it's length
        if ( I2CTransfer(m_devNodeName, m_i2cAdress, &EEPromData) == I2C_IO_OK ) {
            memcpy((void*)data,(void*)&inpBuf[0],l);
            memAddress += l;
            data += l;
            toRead -= l;
        }
        else
            break;
    }
    return(n-toRead);
}

int cF24LC256Private::size()
{
    return 32768;
}
