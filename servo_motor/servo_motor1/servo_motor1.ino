#include "Servo.h"
int mot_pin = D7;
int pot_pin = A0;

Servo servo;
int value;
void setup() {
  servo.attach(mot_pin);
}
void loop() {
  value = analogRead(pot_pin);
  value = map(value, 0, 1023, 0, 180);
  servo.write(value);
  delay(15);
}