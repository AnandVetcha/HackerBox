<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box16/Pictures/AtTiny85_PINOUT.PNG" alt="ATtiny85 Pinout">

Getting Started Using Arduino IDE:
- Installing The Board
  - In File->Preference under additional board manager include the following path. If you already have an existing path then you can separate the entries by comma.
  Path: "https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json"
  - Under "Tools->Board:->Boards Manager" search for "attiny by David A. Mellias" and install it. Once installiation is complete restart the IDE
- Burning bootloader
  - ATTiny85 Pin Connection with Arduino UNO
    - ATTiny85 VCC pin to Arduino 5V
    - ATTiny85 GND pin to Arduino GND
    - ATTiny85 Pin 0 to Arduino Pin 11 
    - ATTiny85 Pin 1 to Arduino Pin 12 
    - ATTiny85 Pin 2 to Arduino Pin 13 
    - ATTiny85 Reset Pin to Arduino Pin 10
   - Open Blank Arduino sketch. Under tools set following configuration and select "Tools->Burn Bootloader"
    - Board : ATtiny25/45/85
    - Processor : ATtiny85
    - Clock : Internal 8Mhz
    - Programmer : Arduino as ISP
    - Port : Select correct COM Port
- Uploading Blink sketch
  - Open a Blink Sketck from "File->Examples->01.Basics->Blink" and set LED Pin to "0" (i.e. ATtiny85 Pin 0)
  - Select Upload
  - Now connect "Red Led with 220ohn resistor in series" to Pin 0 and you observe that Led will blink
