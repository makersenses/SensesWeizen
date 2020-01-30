const int sw1 = 32;
const int sw2 = 34;
const int sw3 = 26;
byte cnt = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
}

void loop()
{

  int sw1Val = digitalRead(sw1);
  int sw2Val = digitalRead(sw2);
  int sw3Val = digitalRead(sw3);

  if (sw1Val == 0) {
    delay(200);
    cnt++;
    Serial.println(cnt);
  }

  else if (sw2Val == 0) {
    delay(200);
    cnt--;
    Serial.println(cnt);
  }

  else if (sw3Val == 0) {
   delay(200);
    cnt = 0;
    Serial.println(cnt);
  }
}
