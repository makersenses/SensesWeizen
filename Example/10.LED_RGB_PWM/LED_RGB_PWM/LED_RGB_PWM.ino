const int greenPin =  32; 
const int redPin   =  26;  
const int bluePin  =  13;  

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(bluePin, ledChannel);

  pinMode(redPin, OUTPUT);   
  pinMode(greenPin, OUTPUT);
  
  digitalWrite(redPin, LOW);  
  digitalWrite(greenPin, LOW); 
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
