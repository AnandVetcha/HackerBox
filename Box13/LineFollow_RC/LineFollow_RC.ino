/**************************************************************
 * This example runs directly on ESP8266 chip
 * using the Blynk platform and mobile application.
 * In the Blynk App you control the car in following modes:
 *  - Manual
 *  - Line Follower Mode
 *  
 * Change Motor connection pin ,WiFi ssid, password, 
 * and Blynk auth token to run :)
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define RightMotorSpeed 5
#define RightMotorDir   0
#define LeftMotorSpeed  4
#define LeftMotorDir    2
#define echoPin 13 // Echo Pin
#define trigPin 12 // Trigger Pin
#define LeftIR  14   // D5 
#define RightIR  15  // D8
ADC_MODE(ADC_VCC);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "*******";
char ssid[] = "*******";
char pass[] = "*******";

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
float Input_Voltage; //To store Battery Voltage
int RC_mode = 0;  //0 - manual ; 1 - auto
int dir_to_turn = 0; //0 - Left; 1- Right
int LeftIR_val = 0;
int RightIR_val = 0;

int Speed = 500; 

SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //randomSeed(1);
  pinMode(LeftIR, INPUT);
  pinMode(RightIR, INPUT);
}

void loop()
{
  Blynk.run();
  if(RC_mode) {
    //Serial.print("In Line follower mode\n");    
    LeftIR_val =  digitalRead(LeftIR);
    //Serial.print("LeftIR value:");
    //Serial.print(LeftIR_val);
    //Serial.print("\n");
    RightIR_val =  digitalRead(RightIR);
    //Serial.print("RightIR value:");
    //Serial.print(RightIR_val);
    //Serial.print("\n");

    if (LeftIR_val==0 && RightIR_val==0) {
      // Move forward
      //Serial.print("  Forward");
      Forward();
    } else if (LeftIR_val==1 && RightIR_val==0){
      //Turn Left
      //Serial.print("  Left");
      Left();
    } else if (LeftIR_val==0 && RightIR_val==1){
      //Turn Right
      //Serial.print("  Right");
      Right();
    } else {
      //halt
      //Serial.print("  Stop");
      halt();
    }
    
  } else {
    //Serial.print("In Manual Mode\n");
  }
  //delay(500);
}

BLYNK_WRITE(V6) {
  RC_mode = param.asInt();
  halt();
}

BLYNK_READ(V5) {
  Input_Voltage = analogRead(A0) / 10000;
  Blynk.virtualWrite(V5,Input_Voltage);
}

BLYNK_READ(V4) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  if (distance >= maximumRange || distance <= minimumRange){
    Blynk.virtualWrite(V4,distance);
  } else {
    Blynk.virtualWrite(V4,distance);
  }  
}

void halt() {
  //digitalWrite(RightMotorSpeed, LOW);
  //digitalWrite(LeftMotorSpeed, LOW);

  //Analog Control
  analogWrite(RightMotorSpeed, 0);
  analogWrite(LeftMotorSpeed, 0);
}

void Right() {
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir, HIGH);
  //digitalWrite(RightMotorSpeed, HIGH);
  //digitalWrite(LeftMotorSpeed, HIGH);

  //Analog Control
  analogWrite(RightMotorSpeed, Speed);
  analogWrite(LeftMotorSpeed, Speed);
}

void Left() {
  digitalWrite(RightMotorDir, LOW);
  digitalWrite(LeftMotorDir, LOW);
  //digitalWrite(RightMotorSpeed, HIGH);
  //digitalWrite(LeftMotorSpeed, HIGH);

  //Analog Control
  analogWrite(RightMotorSpeed, Speed);
  analogWrite(LeftMotorSpeed, Speed);
}

void Reverse() {
  digitalWrite(RightMotorDir, LOW);
  digitalWrite(LeftMotorDir, HIGH);
  //digitalWrite(RightMotorSpeed, HIGH);
  //digitalWrite(LeftMotorSpeed, HIGH);

  //Analog Control
  analogWrite(RightMotorSpeed, Speed);
  analogWrite(LeftMotorSpeed, Speed);
}

void Forward() {
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir, LOW);
  //digitalWrite(RightMotorSpeed, HIGH);
  //digitalWrite(LeftMotorSpeed, HIGH);

  //Analog Control
  analogWrite(RightMotorSpeed, Speed);
  analogWrite(LeftMotorSpeed, Speed);
}

BLYNK_WRITE(V0) {
  if (param[0] && !RC_mode)
    Right();
  else
    halt();
}

BLYNK_WRITE(V1) {
  if (param[0] && !RC_mode)
    Left();
  else
    halt();
}

BLYNK_WRITE(V2) {
  if (param[0] && !RC_mode)
    Reverse();
  else
    halt();
}

BLYNK_WRITE(V3) {
  if (param[0] && !RC_mode)
    Forward();
  else
    halt();
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V6);
}
