#include "Senses_wifi_esp32.h"
#include <OneWire.h>
#include <DallasTemperature.h>

const char *ssid = "your-wifi-network-name";
const char *passw = "your-wifi-password";
const char *userid = "your-senses-user-id";
const char *key = "your-device-key";

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

String response;
float data;

float t;

Senses_wifi_esp32 myiot;

void setup(){
  Serial.begin(9600);
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop(){

  response = "";

  sensors.requestTemperatures();
  Serial.println("done !");
  t = sensors.getTempCByIndex(0);
  Serial.println("t = " + String(t));
  
  response = myiot.send(1,t);
  Serial.println(response);

  delay(10000);
}
