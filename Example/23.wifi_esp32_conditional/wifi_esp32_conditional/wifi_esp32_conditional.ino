#include "Senses_wifi_esp32.h"
#include "DHT.h"

#define PUMP_PIN 13
#define DHTPIN 32
#define DHTTYPE DHT22
int control_port = 1;
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "";
const char *passw = "";

const char *userid = "";
const char *key = "";

String response;
int slot_number = 1;
 

float t, h;

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  dht.begin();
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {
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

  response = myiot.send(1, t);
  Serial.println(response);

  response = myiot.send(2, h);
  Serial.println(response);

  response = myiot.getDigitalControl(control_port);
  Serial.println(response);

  if (response == "on") {
    digitalWrite(PUMP_PIN, HIGH);
  }

  if (response == "off") {
    digitalWrite(PUMP_PIN, LOW);
  }
  
  delay(3000);
}