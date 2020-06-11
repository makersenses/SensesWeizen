#include "Senses_wifi_esp32.h"
#include <SoftwareSerial.h>

const char *ssid = "....";
const char *passw = "....";
const char *userid = "....";
const char *key = "....";

String response;
bool current_state = false;
bool last_state = false;
int control_port = 1;

Senses_wifi_esp32 myiot;

#define txPin 32  // Weizen 32  <----->  Rx HC12
#define rxPin 34  // Weizen 34  <----->  Tx HC12
SoftwareSerial HC12(rxPin, txPin);


void setup() {

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);

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

  Serial.print("HC-12 available... ");
  HC12.write("AT+DEFAULT");
  delay(1000);
  while (HC12.available() > 0) {
    Serial.write(HC12.read());
  }
  Serial.println();
  Serial.println("initialization done.");

  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}


void loop() {

  response = myiot.getDigitalControl(control_port);

  if (response == "on" )
  {
    current_state = true;
    if (current_state != last_state)
    {
      Serial.println(response);
      HC12.println("ON");
      last_state = true;
    }
  }

  if (response == "off" )
  {
    current_state = false;
    if (current_state != last_state)
    {
      Serial.println(response);
      HC12.println("OFF");
      last_state = false;
    }
  }


  while (HC12.available() > 0 ) {
    String str = HC12.readString();
    if (str == "OK-ON\r\n") {
      Serial.print(str);
      response = myiot.send(1, 1);
      Serial.println(response);
    }

    if (str == "OK-OFF\r\n") {
      Serial.print(str);
      response = myiot.send(1, 0);
      Serial.println(response);
    }
  }
}
