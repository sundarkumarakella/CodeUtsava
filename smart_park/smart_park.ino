// IR Obstacle Collision Detection Module
// Henry's Bench

int led1 = 8 ;
int led2 = 12 ;
int opin1 = 5 ;
int opin2 = 4 ;// This is our input pin
int isObstacle1 = HIGH;
int isObstacle2 = HIGH;// HIGH MEANS NO OBSTACLE

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(opin1, INPUT);
  pinMode(opin2, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  isObstacle1 = digitalRead(opin1) ;
  isObstacle2 = digitalRead(opin2) ;
   
  if (isObstacle1 == LOW)
  {
    Serial.println("CLEAR");
    digitalWrite(led1, HIGH);
    delay(500);
  }
  else
  {
    Serial.println("OBSTACLE FROM SLOT 1");
    digitalWrite(led1, LOW);
    delay(500);
  }
  
  if (isObstacle2 == LOW)
  {
    Serial.println("CLEAR");
    digitalWrite(led2, HIGH);
    delay(500);
  }
  else
  {
    Serial.println("OBSTACLE FROM SLOT 2");
    digitalWrite(led2, LOW);
    delay(500);
  }
}

