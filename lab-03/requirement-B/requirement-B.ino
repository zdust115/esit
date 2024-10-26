#define LED 5           // D1(gpio5)
#define LIGHTSENSOR A0  // A/D Port
int ledstate = 0;
int redvalue = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  // Initialize the LED pin as an output
  redvalue = millis();
}
void loop() {
  int value = analogRead(LIGHTSENSOR);
  delay(1000);
  Serial.println(value);
  if (value < 700) {
    if (millis() - redvalue >= 350) {
      ledstate = !ledstate;
      digitalWrite(LED, ledstate);
      redvalue = millis();
    }
    //blinks
  } else {
    digitalWrite(LED, LOW);
  }
}