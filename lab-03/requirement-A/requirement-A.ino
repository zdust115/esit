#define LED 5 // D1(gpio5)
#define LIGHTSENSOR A0 // A/D Port
void setup() {
// Initialize the LED pin as an output
}
void loop() {
int value = analogRead(LIGHTSENSOR);
delay(1000);
Serial.println(value);
if(value > 700) digitalWrite(LED, LOW);
else digitalWrite(LED, HIGH);
}