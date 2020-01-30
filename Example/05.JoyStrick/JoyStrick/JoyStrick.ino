const int VRx = 32;
const int VRy = 34;
const int SW  = 26;

void setup() {                                              
  Serial.begin(9600);
  pinMode(SW,  INPUT_PULLUP);
  analogReadResolution(10);
}

void loop() {
  int VRxVal = analogRead(VRx);
  int VRyVal = analogRead(VRy);
  int SWVal  = digitalRead(SW);

  Serial.print("VRxVal = "); Serial.println(VRxVal);
  Serial.print("VRyVal = "); Serial.println(VRyVal);
  Serial.print("SWVal  = "); Serial.println(SWVal);
  Serial.println("==========");

  if (VRxVal == 0) {
    Serial.println("LEFT");
  }
  else if (VRxVal >= 1000) {
    Serial.println("RIGHT");
  }
  if (VRyVal == 0) {
    Serial.println("UP");
  }
  else if (VRyVal >= 1000) {
    Serial.println("DOWN");
  }
  if (SWVal == HIGH) {
    Serial.println("ON");
  }
  else {
    Serial.println("OFF");
  }
  delay(250);
}                                                                   
