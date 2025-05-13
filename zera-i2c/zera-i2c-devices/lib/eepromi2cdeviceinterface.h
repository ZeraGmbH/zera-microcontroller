#ifndef EEPROMI2CDEVICEINTERFACE_H
#define EEPROMI2CDEVICEINTERFACE_H

#include <QtGlobal>
#include <memory>

class EepromI2cDeviceInterface
{
public:
    static constexpr int capacity24LC256 = (1 << 15);
    static constexpr int capacity24LC512 = (1 << 16);
    EepromI2cDeviceInterface(int byteCapacity) :
        m_byteCapacity(byteCapacity)
    {}
    virtual ~EepromI2cDeviceInterface() = default;
    virtual int WriteData(char* data, ushort count, ushort adr) = 0;
    virtual int ReadData(char* data, ushort count, ushort adr) = 0;
    virtual int Reset() = 0;
    int getByteSize() const { return m_byteCapacity; }
protected:
    const int m_byteCapacity;
};

typedef std::unique_ptr<EepromI2cDeviceInterface> I2cFlashInterfacePtrU;

#endif // EEPROMI2CDEVICEINTERFACE_H
