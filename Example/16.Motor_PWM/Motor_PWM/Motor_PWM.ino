const int motor_AL =  32; 
const int motor_AR =  26;    

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor_AL, ledChannel);

  pinMode(motor_AL, OUTPUT);  
  pinMode(motor_AR, OUTPUT);  
    
  digitalWrite(motor_AR, LOW); 
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){    
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){ 
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}    
                                                                              
                                                                                                                   
