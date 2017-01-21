/*
This skectch was one of the sample skectch for NodeMCU provided
by HackerBoxes.com. Then its was modified as required.
*/

#define echoPin 13 // Echo Pin connected to D1 pin of NodeMCU
#define trigPin 12 // Trigger Pin connected to D6 pin of NodeMCU

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}

void loop() {
  distance = getDistance();
  Serial.println(distance); 
  delay(50);
}

/*
Create a function that will return the
distance estimated by ultrasonic sesnor.
It will return -1 if the estimated distance 
is more than 200
*/

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  if (distance >= maximumRange || distance <= minimumRange){
    return -1;
  } else {
    return distance;
  }  
}
