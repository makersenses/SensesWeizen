#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

#include "Senses_wifi_esp32.h"

const char *ssid = "your-wifi-network-name";
const char *passw = "your-wifi-password";
const char *userid = "your-user-id";
const char *key = "your-device-key";

String response;

Adafruit_SHT31 sht31 = Adafruit_SHT31();
Senses_wifi_esp32 myiot;

void setup(){
  Serial.begin(9600);

  /* Enabled Vcc for TonyS X1*/
  myiot.setPowerOn();
  
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);

  while (!Serial)
    delay(10);

  if (!sht31.begin(0x44)) {   /* SHT31 sensor I2C address : 0x44 */
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  
}

void loop(){

  response = "";

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  response = myiot.send(1,t);
  response = myiot.send(2,h);
  
  Serial.println(response);

  delay(10000);
}
