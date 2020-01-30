int trigPin = 32;    
int echoPin = 26;  
long duration, cm;
 
void setup() { 
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) * 0.0347362 ;     
 
  Serial.print(cm); Serial.print("cm");  Serial.println();
  
  delay(250);
}                                                                       
