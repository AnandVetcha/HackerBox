<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box17/Pictures/ESP8266_Relay.jpg" alt="Internet connected Relay">

Things Required:
- ESP8266
- Relay

Connections:
- ESP8266 is powerved with 3.3V and GND
- Relay is powerved with 5V and GND
- IO2 Pin of ESP8266 is connected to IN1 Pin of Relay
  
Before uploading sketch:
- Enter WIFI ssid and password in the sketch
- Connect IO0 pin to GND and EN (also known as CH_PD) pin to 3.3V and restart the board by switching off and switching on the power
  
After uploading the sketch:
- Open the Serial terminal to get the IP address of the webserver. Visit that IP address to control the relay. 
