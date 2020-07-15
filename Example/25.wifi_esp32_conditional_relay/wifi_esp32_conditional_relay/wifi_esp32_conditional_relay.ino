#include "Senses_wifi_esp32.h"
#define pump_pin 13

const char *ssid = "your-wifi-network-name";
const char *passw = "your-wifi-password";
const char *userid = "your-senses-user-id"; /* You can get it at https://www.sensesiot.com/accountinfo */
const char *key = "your-device-key"; /* You can get it at https://www.sensesiot.com/myiotgarage */ 
 
String response;
int control_pump = 1;
int status_pump  = 1;

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(9600);
  pinMode(pump_pin, OUTPUT);
  digitalWrite(pump_pin, LOW);
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {

  response = myiot.getDigitalControl(control_pump);
  Serial.println(response);

  if (response == "on") {
    digitalWrite(pump_pin, HIGH);

    response = myiot.send(status_pump, 1);
    Serial.println(response);
  }

  if (response == "off") {
    digitalWrite(pump_pin, LOW);
    response = myiot.send(status_pump, 0);
    Serial.println(response);
  }  

  delay(1000);
}
