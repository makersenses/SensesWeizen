#include <TinyGPS++.h> 
#define gpsSerial Serial1 
#define TX_PIN  32 //  MCU 32 <---> Rx GPS
#define RX_PIN  34 //  MCU 34 <---> Tx GPS
    
TinyGPSPlus gps;
 
void setup()
{
  Serial.begin(9600);                                                           
  gpsSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); 
}

void loop()
{ 
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();                                                          

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("    Speed: ")); 
  if (gps.speed.isValid())
  {
    Serial.print(gps.speed.kmph(), 6);  
  }
  else {  
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
