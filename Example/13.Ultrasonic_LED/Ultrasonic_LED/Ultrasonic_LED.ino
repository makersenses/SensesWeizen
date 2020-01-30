int trigPin  = 32;
int echoPin  = 26;

int greenPin = 21;  
int redPin   = 22;   
int bluePin  = 33;   

long duration, cm;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenPin,  OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop() {

  digitalWrite(trigPin, LOW);  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) * 0.0347362 ;

  Serial.print(cm); Serial.print("cm");  Serial.println();

  if (cm <= 5) { 
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin  , LOW);
    digitalWrite(bluePin , LOW);
  }

  else if (cm <= 10) { 
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin  , LOW);
    digitalWrite(bluePin , LOW);
  }

  else if (cm <= 15) { 
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin  , HIGH);
    digitalWrite(bluePin , LOW);
  }

  else if (cm <= 20 || cm > 25) {
    digitalWrite(greenPin  , LOW);                                                                                        
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin , HIGH);
  }

  delay(250);
}
