const int analogInPin = 34; 
int sensorValue = 0;      
int outputValue = 0;  

void setup() { 
  Serial.begin(9600);
  analogReadResolution(10);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin); 
  outputValue = map(sensorValue, 0, 1023, 0, 99);  
 
  Serial.print("sensor = ");     Serial.print(sensorValue);  
  Serial.print("\t output = ");  Serial.println(outputValue); 

  delay(1000); 
}
