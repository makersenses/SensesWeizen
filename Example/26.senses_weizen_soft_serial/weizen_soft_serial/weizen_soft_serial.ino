#define softSerial Serial1 
#define TX_PIN  32 //  MCU 32 <---> Rx GPS
#define RX_PIN  34 //  MCU 34 <---> Tx GPS
    
 
 
void setup()
{
  Serial.begin(115200);                                                           
  softSerial.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); 
}

void loop() {
  while (softSerial.available() > 0) {
    Serial.write(softSerial.read());
  }
  while (Serial.available() > 0) {
    softSerial.write(Serial.read());
  }

}

 
