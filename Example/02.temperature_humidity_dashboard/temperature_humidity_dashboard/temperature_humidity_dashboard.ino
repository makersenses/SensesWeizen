#include "Senses_wifi_esp32.h"
#include "DHT.h"
#define DHTPIN 32
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);                                       

const char *ssid = "BOOM_WiFi";
const char *passw = "076434654";
const char *userid = "122";
const char *key = "p3itsvhtzzj7";

int slot_number_temp = 1;
int slot_number_humidity = 2;

Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("Senses Platfrom in WEIZEN");
  String response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {

  float  t = dht.readTemperature();
  float  h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  String response = myiot.send(slot_number_temp, t);
  Serial.println(response);

  response = myiot.send(slot_number_humidity, h);
  Serial.println(response);

  Serial.print("Humidity: ");     Serial.print(h);  Serial.println(" % ");
  Serial.print("Temperature: ");  Serial.print(t);  Serial.println(" °C ");

  delay(2000);
}
