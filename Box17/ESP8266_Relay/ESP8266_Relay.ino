
/* Internet Connected Relay using ESP8266
 *  Connections:
 *  ESP8266 is powerved with 3.3V and GND
 *  Relay is powerved with 5V and GND
 *  IO2 Pin of ESP8266 is connected to IN1 Pin of Relay
 *  
 *  Before uploading sketch:
 *  Enter WIFI ssid and password in the sketch
 *  Connect IO0 pin to GND and EN pin to 3.3V and restart the board by switching off and switching on the power
 *  
 *  After uploading the sketch:
 *  Open the Serial terminal to get the IP address of the webserver. Visit that IP address to
 *  control the relay * 
*/


#include <ESP8266WiFi.h>
 
const char* ssid = "*************";        //type your ssid
const char* password = "**************";   //type your password
 
int Relay1 = 2;         // GPIO2 of ESP8266
int ServerPort = 96;    // Port number corresponding to webserver

WiFiServer server(ServerPort);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, HIGH);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.print(ServerPort);
  Serial.println("/");
    
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
  int value = LOW;
  if (request.indexOf("/Relay1=ON") != -1) {
    digitalWrite(Relay1, LOW);
    value = HIGH;
  } 
  if (request.indexOf("/Relay1=OFF") != -1){
    digitalWrite(Relay1, HIGH);
    value = LOW;
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/Relay1=ON\">here</a> turn Relay1 ON<br>");
  client.println("Click <a href=\"/Relay1=OFF\">here</a> turn Realy1 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
