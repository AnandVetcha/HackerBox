/**************************************************************
 * This example runs directly on ESP8266 chip
 * 
 * D0 pin of IR reflectivity sensor is connected to 
 * D5 pin of NodeMCU
 **************************************************************/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define LeftIR  14   // D5 

int LeftIR_val = 0;

SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  pinMode(LeftIR, INPUT);
}

void loop()
{
    LeftIR_val =  digitalRead(LeftIR);
    Serial.print("LeftIR value:");
    Serial.print(LeftIR_val);
    Serial.print("\n");

    delay(500);
}
