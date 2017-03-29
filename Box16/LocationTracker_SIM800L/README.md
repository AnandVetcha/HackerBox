<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box16/Pictures/SerialOutput.PNG" alt="Tracker Location">

Things Required:
- SIM800L
- Arduino UNO or equilavelent

Interfacing:
- SIM800L:
VCC -> 5.0V;
GND -> GND;
SIM800L TX -> D8;
SIM800L RX -> D7;

SIM800L module will be used to fetch nearby cell tower information. Using this data custom opencellid.org web link will be printed on serial monitor. This web link will display current approximate location of SIM800L module.
