/*
 * Write data into NFC MIFARE Ultralight Card
 * 
 * Author:      Anand Satya Vetcha
 * Github Link: https://github.com/AnandVetcha
 * 
 * Pin Connection:
 * MFRC522 <---> Arduino Nano V3
 *  RST      - D9
 *  SDA(SS)  - D10
 *  MOSI     - D11
 *  MISO     - D12
 *  SCK      - D13
 */


#include <SPI.h>
#include <MFRC522.h>

#define RstPIN         9          // Depends on Pin hookup
#define SsPIN          10         // Depends on Pin hookup

MFRC522 mfrc522(SsPIN, RstPIN);  // Create MFRC522 instance
MFRC522::StatusCode status;
byte Data_to_write[] = { 0x0F, 0x00, 0x00, 0x00 };  // Provide only 4 bytes of data
byte Page_to_write = 0x07;                          // Provide any one page location between 0x04 to 0x0F which corresponds to page 4 to 15

void setup() {
  Serial.begin(9600);                 // Initialize serial communications with the PC
  while (!Serial);                    // Wait till serial port is opened
  SPI.begin();                        // Initialize SPI bus
  mfrc522.PCD_Init();                 // Initialize MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan for a PICC"));
  Serial.println(F("PICC : Proximity Integrated Circuit Card"));
}

void loop() {
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  Serial.println();
  Serial.println(F("New PICC found"));

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.println(F("New PICC UID information is read"));

  Serial.println();
  
  // if PICC an suitable NFC tag, data to be 
  // written is 4 bytes long and page location is 
  // greater than 0x03 then write the data
  if (mfrc522.uid.sak == 0x00 && sizeof(Data_to_write) == 0x04  && Page_to_write >= 0x04 && Page_to_write <= 0x0F) {
    Serial.println(F("PICC is suitable NFC tag and will try to write data"));
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(Page_to_write, Data_to_write, sizeof(Data_to_write));
    if (status == MFRC522::STATUS_OK) {
        Serial.println(F("Successfully written data to MIFARE Ultralight NFC tag :) "));
        Serial.println();
        Serial.println(F("New data stored in NFC tag:"));
        mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    } else {
        Serial.print(F("Couldnt write data to MIFARE Ultralight NFC tag :( "));
        Serial.println(mfrc522.GetStatusCodeName(status));
    }
  } else {
    if (mfrc522.uid.sak != 0x00) {
      Serial.println(F("Tag is not NFC type. Esiting code cannot write the data"));
    }
    if (sizeof(Data_to_write) != 0x04) {
      Serial.println(F("Please provide only 4 bytes of data to write"));
    }
    if (Page_to_write < 0x04 || Page_to_write > 0x0F) {
      Serial.println(F("Data stored in page located between 0x00 to 0x03 has special significance."));
      Serial.println(F("Its better to leave thoes pages alone. Please provide page number between 0x04 to 0x15."));
    }
  } 
}
