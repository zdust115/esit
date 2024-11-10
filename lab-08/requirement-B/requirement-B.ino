uint8_t GPIO_Pin2 = D2;
uint8_t GPIO_Pin3 = D4;
void IRAM_ATTR IntCallbackRising();
void IRAM_ATTR IntCallbackFalling();

void setup() {
  Serial.begin(115200);
  pinMode(GPIO_Pin2, INPUT);
  pinMode(GPIO_Pin3, INPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin2), IntCallbackRising, RISING);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin3), IntCallbackFalling, FALLING);
}
void loop() {
}
void IRAM_ATTR IntCallbackRising() {
  Serial.print("Rising Time (ms): ");
  Serial.println(millis());
}

void IRAM_ATTR IntCallbackFalling() {
  Serial.print("Falling Time (ms): ");
  Serial.println(millis());
}