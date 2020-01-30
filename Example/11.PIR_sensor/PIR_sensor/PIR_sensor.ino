const int pirPin    = 4;
const int buzzerPin = 22;
      int pirState  = 0;

void setup() 
{
  ledcWriteTone(0, 1000);
  pinMode(pirPin, INPUT); 
  pinMode(buzzerPin, OUTPUT); 
}

void loop() {
  pirState = digitalRead(pirPin); 

  if (pirState == HIGH) {
    ledcAttachPin(buzzerPin, 0); delay(500);
    ledcDetachPin(buzzerPin);    delay(500);
  }
  
  else { 
    ledcDetachPin(buzzerPin);
  }
}
