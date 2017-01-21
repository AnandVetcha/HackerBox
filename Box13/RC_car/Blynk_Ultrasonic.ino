 * This example runs directly on NodeMCU
 * using the Blynk platform and mobile application.
 * Ultrasonic sensor (HC -SR04) is connected to the RC car
 * 
 * Change WiFi ssid, password, and Blynk auth token to run :)
 ***************************************************************

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define RightMotorSpeed 5 // 
#define RightMotorDir   0 // Motor connected. This pin connection will depend on 
#define LeftMotorSpeed  4 // the motors orientataion, location and pin connections
#define LeftMotorDir    2 // to teh motor sheild


#define echoPin 13        // Echo Pin (Ultrasonic distance sesnsor)
#define trigPin 12        // Trigger Pin  (Ultrasonnic diatnce sensor)
ADC_MODE(ADC_VCC);        

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxx";
char ssid[] = "xxxxxxxxxxxxxx";
char pass[] = "xxxxxxxxxxxxxx";

int maximumRange = 200;   // Maximum range needed
int minimumRange = 0;     // Minimum range needed
long duration, distance;  // Duration used to calculate distance
float Input_Voltage;      //To store Battery Voltage

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
  //timer.setInterval(500, getDistance);
}

void loop()
{
  Blynk.run();
}

BLYNK_READ(V5)
{
  Input_Voltage = analogRead(A0) / 10000;
  Blynk.virtualWrite(V5,Input_Voltage);
}

BLYNK_READ(V4)
{
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

void halt()
{
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
}

void forward()
{
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir, HIGH);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void reverse()
{
  digitalWrite(RightMotorDir, LOW);
  digitalWrite(LeftMotorDir, LOW);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void right()
{
  digitalWrite(RightMotorDir, LOW);
  digitalWrite(LeftMotorDir, HIGH);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void left()
{
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir, LOW);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

BLYNK_WRITE(V0)
{
  if (param[0])
    forward();
  else
    halt();
}

BLYNK_WRITE(V1)
{
  if (param[0])
    reverse();
  else
    halt();
}

BLYNK_WRITE(V2)
{
  if (param[0])
    right();
  else
    halt();
}

BLYNK_WRITE(V3)
{
  if (param[0])
    left();
  else
    halt();
}
