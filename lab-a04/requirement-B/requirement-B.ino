#include "Servo.h"
int mot_pin = D7;
int pot_pin = A0;

int led1 = D1;
int led2 = D2;


Servo servo;
int value;
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  servo.attach(mot_pin);
}
void loop() {
  Serial.println(value);
  value = analogRead(pot_pin);
  value = map(value, 15, 1023, 0, 180);
  servo.write(value);
  if(value == 180) digitalWrite(led1,HIGH);
  if(value == 0) digitalWrite(led2,HIGH);
  if(value >0 && value < 180) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
  
  delay(15);
}
