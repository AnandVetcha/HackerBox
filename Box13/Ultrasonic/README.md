<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box13/Pictures/Ultrasonic.jpg" alt="Ultrasonic Sensor">

HC - SR04 is the name of the ultrasonic sensor that was used for this sketch.

Sensor pin conenctions with NodeMCU:
- VCC to NodeMCU VIN 
- GND to NodeMCU G
- Echo to NodeMCU pin D7 (GPIO13) 
- Trig to NodeMCU pin D6 (GPIO12)

Functioning of Ultrasonic sensor:
After the Trigger pin is set to high for 10um, module will send out 8 cycle burst of ultrasonic soud and will simultaneoulsy set high vaule to Echo pin. When the Echo module senses the reflected ultrasonic sound it will immediately go low. Arduino's "pulseIn" can be used to measure the duration for which Echo pin high. We can get the distance if this duration is multiplied by speed of air and divided by 2.
