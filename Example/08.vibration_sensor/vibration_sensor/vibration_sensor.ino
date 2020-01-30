const int vibrationPin = 32;   
void setup() {
  Serial.begin(9600); 
  pinMode(vibrationPin, INPUT);
}

void loop() { 
  int vibrationState = digitalRead(vibrationPin);
 
  if (vibrationState == HIGH) { 
    Serial.println("Alarm On");
  } 
  else {  
    Serial.println("Alarm Off");
  }
}                                                         
