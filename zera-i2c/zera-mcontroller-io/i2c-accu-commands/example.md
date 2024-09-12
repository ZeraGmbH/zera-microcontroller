## Some helpful examples for communication from Linux to accu-controller

Accu I2c-communication introduces new features
* To access directly requests to microcontroller have to go out first. Sytstemcontroller
  needs time to switch so check completion. After accu commands completed, systemcontroller has to be switched back to communicate with accu (search below for 'Ext-i2c-bus')
* For simple commands as read version tunneling was invented (search below for 'tunneled')


### Adresses:
* System Controller (5860) 0x22
* Relay Controller  0x21
* Accu Controller (5929)  0x0A

---

* Check battery status at system controller:\
 echo $(zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c210 -l1)\
bp Battery_Present = 0\
bp_Battery_is_Charging = 1\
bp_External_power_supply = 7

* Request access to Ext-i2c-bus (to accu controller):\
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c50 -p'0x01'

* Check if access access to Ext-i2c-bus is available:\
echo $(zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c51 -l1)\
Bit0 = 0  &rarr; access to system-controller\
Bit0 = 1 &rarr;  access to accu-controller

* Give Ext-i2c-bus back to systemcontroller:\
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c50 -p'0x00'

---

* Switch from application to bootloader\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c8

* Switch from bootloader to application\
zera-mcontroller-io -i/dev/i2c-0 -I0A -c1

---

* Request PCB/SW accu description ***direct***\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c2 -lx -a1

* Request software accu version ***direct***\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c3 -lx -a1

* Request software accu info ***direct/bootloader***\
zera-mcontroller-io -i/dev/i2c-0 -I0A -c0 -lx -a1

---
* Request accu PCB/SW description ***tunneled***\
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c54 -p'0x0A 0x00 0x02' -lx -a1

* Request accu software version ***tunneled***\
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c54 -p'0x0A 0x00 0x03' -lx -a1
