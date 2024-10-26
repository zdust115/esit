#include "Servo.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Usa la libreria LiquidCrystal

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Indirizzo I2C e dimensione del display
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
  Wire.begin(D2, D1);          // SDA su D2, SCL su D1 (ESP8266)
  lcd.begin(16, 2);            // Inizializza il display 16x2
  lcd.backlight();             // Accendi la retroilluminazione
  lcd.setCursor(0, 0);         // Imposta il cursore sulla prima riga
}
void loop() {
  value = analogRead(pot_pin);
  value = map(value, 15, 1023, 0, 180);
  servo.write(value);

  if(value == 180) {
  digitalWrite(led1,HIGH);
  digitalWrite(led2,LOW);
  }
  if(value == 0) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
  }
  if(value >0 && value < 180) {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
  }
  lcd.print(value);  // Mostra il testo
  delay(15);
}
