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

Future Improvements: Using cell tower data and Google geolocation API, i would like to print Latitude/Logitude coordinates to serial monitor. To implement this we need working example of https POST request using SIM800L module. I tried few online examples and it didnt work. If anyone figures it, please share your learnings. :)
