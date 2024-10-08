#ifndef ZERAMCONTROLLERIOFORTEST_H
#define ZERAMCONTROLLERIOFORTEST_H

#include <zeramcontrolleriotemplate.h>

class ZeraMcontrollerIoForTest : public ZeraMControllerIoTemplate
{
public:
    ZeraMcontrollerIoForTest(QString devnode, quint8 adr, quint8 debuglevel);
    void simulateApplicationRunnung();
    void simulateBooloaderRunning();
    atmelRM bootloaderStartProgram() override;
    atmelRM readVariableLenText(quint16 hwcmd, QString& answer, quint8 *extraParam=nullptr, quint16 extraParamLen=0) override;
private:
    ZeraMControllerIoTemplate::atmelRM m_return = cmdfault;
};

#endif // ZERAMCONTROLLERIOFORTEST_H
