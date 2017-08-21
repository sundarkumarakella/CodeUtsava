#include <SoftwareSerial.h>         // including the library for the software serial
#define DEBUG true
SoftwareSerial esp8266(0, 1);    

const int trigPin = 7;            // Making the arduino's pin 8 as the trig pin of ultrasonic sensor
const int echoPin = 8;            // Making the arduino's pin 9 as the echo pin of the ultrasonic sensor

long duration;
int distance;
void setup()
{
  //Serial.begin(9600);         
  esp8266.begin(115200);        
  pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pin
  pinMode(echoPin, INPUT);    // Setting the echoPin as Input pin

  sendData("AT+RST\r\n", 2000, DEBUG);          
  sendData("AT+CWMODE=2\r\n", 1000, DEBUG);     
  sendData("AT+CIFSR\r\n", 1000, DEBUG);        // This command will get the ip address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);     // This will configure the esp for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // This command will turn on the server on port 80
}
void loop()
{
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);        
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2; 

  if (esp8266.available())      
  {
    if (esp8266.find("+IPD,"))
    {
      delay(1000);
      int connectionId = esp8266.read() - 48;
      String webpage = "<h1>IOT Garbage Monitoring System</h1>";
      webpage += "<p><h2>";
      if (distance < 5)
      {
        webpage += " Trash can is Full";
      }
      else {
        webpage += " Trash can is Empty";
      }
      webpage += "</h2></p>";
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId;
      closeCommand += "\r\n";
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  return response;
}
