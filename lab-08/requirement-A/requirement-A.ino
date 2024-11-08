uint8_t GPIO_Pin = D2;
void IRAM_ATTR IntCallback();
void setup() {
  Serial.begin(115200);
  pinMode(GPIO_Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), IntCallback, RISING);
}
void loop() {
}
void IRAM_ATTR IntCallback() {
  Serial.print("Time (ms): ");
  Serial.println(millis());
}