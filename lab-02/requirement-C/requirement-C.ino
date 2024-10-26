int ledpin = 5;  //D1(gpio5)
int button = 4;  //D2(gpio4)
int buttonState = 0;
int ledState = 0;
int tempoCorrente = 0;

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(button, INPUT);
}
void loop() {
  buttonState = digitalRead(button);
  if (buttonState == 1) {
    tempoCorrente = millis();
    ledState = !ledState;
    digitalWrite(ledpin, ledState);
    Serial.print("statoLed: ");
    Serial.println(ledState);
    delay(20);
  }

  if (ledState && millis() - tempoCorrente >= 1000) {
    ledState = 0;
    digitalWrite(ledpin, ledState);
    Serial.print("statoLed: ");
    Serial.println(ledState);
  }
}