#include <SoftwareSerial.h>

#define pump 2   // Arduino Nano 2  <----->  IN Relay
#define txPin 3  // Arduino Nano 3  <----->  Rx HC12
#define rxPin 4  // Arduino Nano 4  <----->  Tx HC12

SoftwareSerial HC12(rxPin, txPin);
long baud = 9600;

void setup() {

  pinMode(pump, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  digitalWrite(pump, LOW);

  Serial.begin(baud);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial monitor available... OK");

  Serial.print("Serial link available... ");
  HC12.begin(9600);
  if (HC12.isListening()) {
    Serial.println("OK");
  } else {
    Serial.println("NOK");
  }

  //test HC-12
  Serial.print("HC-12 available... ");
  HC12.write("AT+DEFAULT");
  delay(1000);
  while (HC12.available() > 0) {
    Serial.write(HC12.read());
  }
  Serial.println();
  Serial.println("initialization done.");
}

void loop() {

  while (HC12.available() > 0 ) {
    String str = HC12.readString();
    if (str == "ON\r\n") {
      Serial.println("Receive ON");
      HC12.print("OK-" + str);
      digitalWrite(pump, HIGH);
    }

    if (str == "OFF\r\n") {
      Serial.println("Receive OFF");
      HC12.print("OK-" + str);
      digitalWrite(pump, LOW);
    }
  }
}
