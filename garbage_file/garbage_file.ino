#include <SoftwareSerial.h>
const int trigPin = 7;
const int echoPin = 6;
SoftwareSerial esp8266(0,1);


void setup() {
  
  esp8266.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  
  long duration, inches, cm;
  
  digitalWrite(trigPin, LOW);
  delay(500);
  digitalWrite(trigPin, HIGH);
  delay(500);
  digitalWrite(trigPin, LOW);
  delay(500);
  
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  delay(1000);
  Serial.print(cm);
  Serial.print("cm");
  delay(1000);
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
