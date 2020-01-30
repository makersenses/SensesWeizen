const int motor_AL =  32; 
const int motor_AR =  26;   
         
void setup() {
  pinMode(motor_AL, OUTPUT);  
  pinMode(motor_AR, OUTPUT);  
}

void loop() { 
    // Left
    digitalWrite(motor_AL, HIGH); 
    digitalWrite(motor_AR, LOW);  
    delay(3000);
    
    // Right
    digitalWrite(motor_AL, LOW); 
    digitalWrite(motor_AR, HIGH);  
    delay(3000);
     
    //Stop
    digitalWrite(motor_AL, LOW); 
    digitalWrite(motor_AR, LOW);  
    delay(3000); 
}   


                                                      
