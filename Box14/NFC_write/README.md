<img src="https://github.com/AnandVetcha/HackerBox/blob/master/Box14/Pictures/NFC_write.jpg" alt="NFC write">

This Required:
- Arduino Nano V3 or equivalent
- MFRC522 RFID reader
- MIFARE Ultralight NFC card or equivalent

Pin Connection:
 * MFRC522 <---> Arduino Nano V3
 *  RST      - D9
 *  SDA(SS)  - D10
 *  MOSI     - D11
 *  MISO     - D12
 *  SCK      - D13
 
Memory organisation in NFC card:

The 512-bit EEPROM memory is organized in 16 pages (i.e. 0x00 to 0x0F) with 4 bytes per page. First for pages contaion NFC UID,
Lock Bytes, One Time Programmable area, etc. Lock Bytes as the name suggests, can prevent new data getting written into NFC card. 
To be on the safer above arduino code will prevent data gettin written into the first 4 pages (i.e. 0x00 to 0x03)
 
MIFARE Ultralight datasheet for reference:
http://www.nxp.com/documents/data_sheet/MF0ICU1.pdf
