int ledpin = 5;  //D1(gpio5)
int button = 4;  //D2(gpio4)
int buttonState = 0;
int ledState = 0;
void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(button, INPUT);
}
void loop() {
  buttonState = digitalRead(button);
  if (buttonState == 1) {
    ledState = !ledState;
    digitalWrite(ledpin, ledState);
    delay(200);
  }
  
}