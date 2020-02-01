#include "DHT.h"
#define DHTPIN 32 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
   
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  Serial.print("Humidity: ");     Serial.print(h);  Serial.println(" % "); 
  Serial.print("Temperature: ");  Serial.print(t);  Serial.println(" °C ");  
  delay(2000);
}
