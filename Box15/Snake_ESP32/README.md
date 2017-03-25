<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box15/Pictures/Snake_ESP32.jpg" alt="Snake Game ESP32">

Things Required:
- ESP32
- Oled Display (SSD1306)
- 4X4 Keypad 

Arduino Library Required:
- Oled Display : Used libraries located at https://github.com/squix78/esp8266-oled-ssd1306/releases . Download the zip file and using Arduino IDE include the libs. Sketch->Include Library-> Add .ZIP Library
- Qlist : You can download them from Arduinos built-in Libraray manager. Sketch->Include Library->Manage Libararies
- Keypad : You can download them from Arduinos built-in Libraray manager. Sketch->Include Library->Manage Libararies

Interfacing:
- Oled Diplay (SSD1306):
VCC -> 3v3;
GND -> GND;
SCL -> IO22;
SDA -> IO21;
- 4X4 Keypad:
First 5 pins from Left to Right -> IO12;IO14;IO27;IO26;IO25

Video:
[Snake Game using ESP32](https://www.youtube.com/watch?v=Favfaeqm_Zo)
