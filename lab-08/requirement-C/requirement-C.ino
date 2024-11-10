uint8_t GPIO_Pin2 = D2;
uint8_t GPIO_Pin4 = D4;
const int LEDPIN = D7;
int timeLastPressed = 0;
int ledstate=LOW;


void setup() {
  Serial.begin(115200);
  pinMode(GPIO_Pin2, INPUT);
  pinMode(GPIO_Pin4, INPUT);
  pinMode(LEDPIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin2), IntCallbackRising, RISING);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin4), IntCallbackFalling, FALLING);
}
void loop() {
  if(ledstate&&(millis()-timeLastPressed>200)){
    ledstate=LOW;
    digitalWrite(LEDPIN, ledstate);
  }
}
ICACHE_RAM_ATTR void IntCallbackRising() {
  Serial.print("Rising Time (ms): ");
  ledstate=HIGH;
  digitalWrite(LEDPIN, ledstate);
  timeLastPressed= millis();
  Serial.println(millis());
}

ICACHE_RAM_ATTR void IntCallbackFalling() {
  Serial.print("Falling Time (ms): ");
  Serial.println(millis());
  timeLastPressed=millis();
  ledstate=HIGH;
  digitalWrite(LEDPIN, ledstate);

}