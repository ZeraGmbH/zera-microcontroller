#include "i2cmultiplexerfactory.h"
#include <i2cmuxerpca9547.h>

I2cMuxerInterface::Ptr I2cMultiplexerFactory::createPCA9547Muxer(QString deviceNode, ushort i2cMuxAddr, quint8 channel0to7)
{
    return std::make_shared<I2cMuxerPCA9547>(deviceNode, i2cMuxAddr, channel0to7);
}

I2cMuxerInterface::Ptr I2cMultiplexerFactory::createNullMuxer()
{
    return std::make_shared<I2cMuxerNull>();
}
