/**
 * Location Tracker using SIM800L
 * Author : Anand Satya
 * Git Repo: 
 * Description: SIM800L module will be used to fetch nearby cell tower information. Using this data custom
 * opencellid.org web link will be printed on serial monitor. This web link will display current approximate 
 * location of SIM800L module.
 * 
 * Acknowledgement:
 * hex to unsigned int function was taken from https://forum.arduino.cc/index.php?topic=123486.0
 */

#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

//Nearby Cell tower information
unsigned int CellId;
unsigned int LocationAreaCode;
unsigned int MobileCountryCode;
unsigned int mobileNetworkCode;
String SIM800L_response;
String Temp;
char temp_char[5];
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
  
   
  Serial.println("Setup Complete!");
  while(!NetwortRegistration()) {
    Serial.println("Waiting for network registration");
    delay(1000);
  }
}
 
void loop() {
  // Get Cell Tower Information
  serialSIM800.write("AT+CENG=3,1\r\n");
  delay(1000);
  SIM800L_response = ReturnResponse();
  //Serial.println(SIM800L_response);
  serialSIM800.write("AT+CENG?\r\n");
  delay(2000);
  SIM800L_response = ReturnResponse();
  Serial.println(SIM800L_response);

  Serial.println();
  Serial.println();
  Serial.println("********* Printing Nearby Cell Tower Information *****************");
  //     Fetching MobileCountryCode
  SIM800L_response = SIM800L_response.substring(SIM800L_response.indexOf("\""));
  //Serial.println(SIM800L_response);
  MobileCountryCode = SIM800L_response.substring(1,SIM800L_response.indexOf(",")).toInt();
  Serial.print("MobileCountryCode :");
  Serial.println(MobileCountryCode);

  //    Fetching mobileNetworkCode
  SIM800L_response = SIM800L_response.substring(SIM800L_response.indexOf(",") + 1);
  //Serial.println(SIM800L_response);
  mobileNetworkCode = SIM800L_response.substring(0,SIM800L_response.indexOf(",")).toInt();
  Serial.print("mobileNetworkCode :");
  Serial.println(mobileNetworkCode);

  //    Fetching LocationAreaCode
  SIM800L_response = SIM800L_response.substring(SIM800L_response.indexOf(",") + 1);
  SIM800L_response.toUpperCase();
  //Serial.println(SIM800L_response);
  Temp = SIM800L_response.substring(0,SIM800L_response.indexOf(","));
  Serial.print("Converting ");
  Serial.print(Temp);
  Serial.println(" from Hex to UnsignedInt"); 
  Temp.toCharArray(temp_char,5);
  LocationAreaCode = hex2int(temp_char);
  Serial.print("LocationAreaCode :");
  Serial.println(LocationAreaCode);

  //    Fetching CellId
  SIM800L_response = SIM800L_response.substring(SIM800L_response.indexOf(",") + 1);
  SIM800L_response.toUpperCase();
  //Serial.println(SIM800L_response);
  Temp = SIM800L_response.substring(0,SIM800L_response.indexOf(","));
  Serial.print("Converting ");
  Serial.print(Temp);
  Serial.println(" from Hex to UnsignedInt"); 
  Temp.toCharArray(temp_char,5);
  CellId = hex2int(temp_char);
  Serial.print("CellId :");
  Serial.println(CellId);

  
  // Print to opencellid URL to get approximate location
  https://opencellid.org/#action=locations.cell&mcc=404&mnc=86&lac=31702&cellid=65002
  Serial.println();
  Serial.println();
  Serial.println("Please visit following link to get the approximate location of the tracker");
  Serial.print("https://opencellid.org/#action=locations.cell&mcc=");
  Serial.print(MobileCountryCode);
  Serial.print("&mnc=");
  Serial.print(mobileNetworkCode);
  Serial.print("&lac=");
  Serial.print(LocationAreaCode);
  Serial.print("&cellid=");
  Serial.println(CellId);
  
  delay(100000);  
}

int hex2int(char *s) {
  int x = 0;
  for(;;) {
    char c = *s;
    if (c >= '0' && c <= '9') {
      x *= 16;
      x += c - '0';
    } else if (c >= 'A' && c <= 'F') {
      x *= 16;
      x += (c - 'A') + 10;
    } else {
      break;
    }
    s++;
  }
  return x;
}


int NetwortRegistration () {
  String response = "";
  //Retun 1 if registered on a network else return 0
  serialSIM800.write("AT+CREG?\r\n");
  delay(1000);

  response = ReturnResponse();
  //Serial.println("Printing response:");
  //Serial.println(response);

  int FirstEndOfLine = response.indexOf("\n");
  int SecondEndOfLine = response.indexOf("\n",FirstEndOfLine +1);

  String SecondLine = response.substring(FirstEndOfLine + 1,SecondEndOfLine);
  //Serial.println("Printing Target line:");
  //Serial.println(SecondLine);
  if (SecondLine.startsWith("+CREG")) {
    int NetworkReg_status = (SecondLine.substring(SecondLine.indexOf(",") + 1,SecondLine.indexOf(",") + 2)).toInt();
    Serial.print("Connection Status:");
    Serial.println(NetworkReg_status);
    if (NetworkReg_status == 1 || NetworkReg_status == 5) {
      return 1; 
    } else {
      return 0;
    }
  } else {
    Serial.println("No connection information");
    return 0;
  }
}

String ReturnResponse () {
  String response = "";
  char letter;
  int counter = 0;

  while (counter < 7  && !serialSIM800.available()) {
    Serial.println("Waiting for Response");
    delay(1000);
    counter = counter + 1;
    Serial.print("    Counter:");
    Serial.println(counter);
    if (counter = 7) {
      response = "No Response";
      return response;
    }
  }

  while (serialSIM800.available()){
    letter = serialSIM800.read();
    response = String(response + letter);
  }
  return response;
}
