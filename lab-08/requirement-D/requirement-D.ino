uint8_t GPIO_Pin2 = D2;
uint8_t GPIO_Pin4 = D4;
const int LEDPIN = D7;
int timeLastPressed = 0;
int ledstate = LOW;
int oldbuttonstate = 0;
int buttonstate = 0;


void setup() {
  Serial.begin(115200);
  pinMode(GPIO_Pin2, INPUT);
  pinMode(GPIO_Pin4, INPUT);
  pinMode(LEDPIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin2), IntCallbackRising, RISING);
  //attachInterrupt(digitalPinToInterrupt(GPIO_Pin4), IntCallbackFalling, FALLING);
}
void loop() {
  gestioneBottone();
  if (ledstate && (millis() - timeLastPressed > 400)) {
    ledstate = LOW;
    digitalWrite(LEDPIN, ledstate);
  }
}
ICACHE_RAM_ATTR void IntCallbackRising() {
  Serial.print("Interrupt Rising Time (ms): ");
  ledstate = HIGH;
  digitalWrite(LEDPIN, ledstate);
  timeLastPressed = millis();
  Serial.println(millis());
}

void gestioneBottone() {
  oldbuttonstate = buttonstate;
  buttonstate = digitalRead(GPIO_Pin4);
  if (buttonstate == HIGH && oldbuttonstate == LOW) {
    Serial.print("Standard Button Time: ");
    Serial.println(millis());
    timeLastPressed = millis();
    ledstate = HIGH;
    digitalWrite(LEDPIN, ledstate);
  }
}