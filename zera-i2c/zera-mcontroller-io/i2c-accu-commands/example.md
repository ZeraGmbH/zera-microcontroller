


Check BATTERY_STATUS System controller
echo $(zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c210 -l1)

Request access to external i2c-bus (accu) System controller
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c50 -p'0x01'

Give i2c-EXT back to systemcontroller
zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c50 -p'0x00'

Check if i2c-bus access is available              
echo $(zera-mcontroller-io -i/dev/i2c-0 -I22 -d0 -c51 -l1)



Switch from APP to bootloader
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c8

Switch from bootloader to APP
zera-mcontroller-io -i/dev/i2c-0 -I0A -c1

Anfrage PCB/SW Beschreibung  (Applikation)
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c2 -lx -a1

Anfrage SW Version (Applikation)
zera-mcontroller-io -i/dev/i2c-0 -I0A -d0 -c3 -lx -a1

Anfrage SW Info  (Bootloader)  -> Antwort "ZBtLoad@AVR ...."
zera-mcontroller-io -i/dev/i2c-0 -I0A -c0 -lx -a1

