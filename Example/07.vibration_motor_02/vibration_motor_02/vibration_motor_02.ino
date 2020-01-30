const int vibrationMotorPin = 18;   

// setting PWM properties
const int freq = 5000;
const int vibrationMotorChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure vibrationMotor PWM functionalitites
  ledcSetup(vibrationMotorChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlvibrationMotor
  ledcAttachPin(vibrationMotorPin, vibrationMotorChannel);
}
 
void loop(){
  // increase the vibrationMotor brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){ 
    ledcWrite(vibrationMotorChannel, dutyCycle);
    delay(15);
  }

  // decrease the vibrationMotor brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(vibrationMotorChannel, dutyCycle);   
    delay(15);
  }
}                                                             
