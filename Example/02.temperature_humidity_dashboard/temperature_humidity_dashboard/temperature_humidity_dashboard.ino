#include "Senses_wifi_esp32.h"
#include "DHT.h"

#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = "";

String response;
int slot_number = 1;
float data;

float t,h;

Senses_wifi_esp32 myiot;

void setup(){
  Serial.begin(9600);
  dht.begin();
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop(){

  response = "";

  /* - DHT sensor reading - */
  t = dht.readTemperature();
  h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Temperature is " + String(t) + " celcuis");
  Serial.println("Humidity is " + String(h) + " %RH");
  Serial.println("----------------------------------------");

  response = myiot.send(1,t);
  Serial.println(response);

  response = myiot.send(2,h);
  Serial.println(response);

  delay(5000);
}