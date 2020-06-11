#include "Senses_wifi_esp32.h"

const char *ssid = "";
const char *passw = "";
const char *userid = "";
const char *key = "";

Senses_wifi_esp32 myiot;
String response;

//------ RAIN ----------------//
int rain_pin = 32;
bool rain_pressed = false;

float rainAmount = 0.3;
int cnt_hr = 0;
int cnt_day = 0;

float rain_hr = 0;
float rain_day = 0;
float rain_total = 0;

unsigned long previousMillis = 0;
const long interval = 60000;

void IRAM_ATTR isr() {
  rain_pressed = true;
}

//------ PUMP ----------------//
int pump_pin = 26;
bool current_state = false;
bool last_state = false;
int control_port = 1;
 
void setup() {
  Serial.begin(115200);
  pinMode(rain_pin, INPUT_PULLUP);
  attachInterrupt(rain_pin, isr, FALLING);
  pinMode(pump_pin, OUTPUT);

  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop() {

  response = "";

  if (rain_pressed) {
    rain_hr    = rain_hr + rainAmount;
    rain_day   = rain_day + rainAmount;
    rain_total = rain_total + rainAmount;
    delay(50);

    Serial.print("rain_hr    : ");  Serial.print(rain_hr);     Serial.println(" mm");
    Serial.print("rain_day   : ");  Serial.print(rain_day);    Serial.println(" mm");
    Serial.print("rain_total : ");  Serial.print(rain_total);  Serial.println(" mm");
    Serial.println(" ======================================");

    rain_pressed = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    cnt_hr++;
    cnt_day++;

    if (cnt_hr > 60) {
      rain_hr = 0;
      cnt_hr = 0;
    }

    if (cnt_day > 1440) {
      rain_day = 0;
      cnt_day = 0;
    }
 
    response = myiot.send(1, rain_hr);
    Serial.println(response);

    response = myiot.send(2, rain_day);
    Serial.println(response);

    response = myiot.send(3, rain_total);
    Serial.println(response);
  }

  response = myiot.getDigitalControl(control_port);

  if (response == "on" )
  {
    current_state = true;
    if (current_state != last_state)
    {
      Serial.print("Status pump : "); Serial.println(response);
      digitalWrite(pump_pin, HIGH);
      last_state = true;
    }
  }

  if (response == "off" )
  {
    current_state = false;
    if (current_state != last_state)
    {
      Serial.print("Status pump : "); Serial.println(response);
      digitalWrite(pump_pin, LOW);
      last_state = false;
    }
  }
}
