int buzzer_pin = 13;
  
void setup() {
  ledcWriteTone(0, 1000);
}

void loop() {
  ledcAttachPin(buzzer_pin, 0);
  delay(500);
  ledcDetachPin(buzzer_pin);
  delay(500);
}
