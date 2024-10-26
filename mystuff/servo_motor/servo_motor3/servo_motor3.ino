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
  value = analogRead(pot_pin);
  value = map(value, 15, 1023, 0, 180);
  servo.write(value);

  Serial.print("Valore: ");
  Serial.print(value);
  if(value == 180) {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  Serial.println(", Led1 Acceso, Led2 Spento");
  }
  if(value == 0) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    Serial.println(", Led1 Spento, Led2 Acceso");
  }
  if(value >0 && value < 180) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    Serial.println(", Led1 Spento, Led2 Spento");

  }


  
  delay(15);
}
