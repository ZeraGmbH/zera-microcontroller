## Some helpful examples for communication from Linux to accu-controller

The special feature is that access to the accu controller must **first be enabled** via the system controller


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

* Give Ext-i2c-bus back to systemcontroller:\
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c50 -p'0x00'

* Check if i2c-bus access is available:\
echo $(zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c51 -l1)\
Bit0 = 0  &rarr; access to system-controller\
Bit0 = 1 &rarr;  acces to accu-controller

---

* Switch from application to bootloader\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c8

* Switch from bootloader to application\
zera-mcontroller-io -i/dev/i2c-0 -I0A -c1

---

* Request PCB/SW decription (application)\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c2 -lx -a1

* Request software version (application)\
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c3 -lx -a1

* Request software info (bootloader)\
zera-mcontroller-io -i/dev/i2c-0 -I0A -c0 -lx -a1

