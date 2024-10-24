#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Usa la libreria LiquidCrystal

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Indirizzo I2C e dimensione del display

void setup() {
  Wire.begin(D2, D1);  // SDA su D2, SCL su D1 (ESP8266)
  lcd.begin(16, 2);    // Inizializza il display 16x2
  lcd.backlight();     // Accendi la retroilluminazione
  lcd.setCursor(0, 0); // Imposta il cursore sulla prima riga
  lcd.print("Hello, world!");  // Mostra il testo
}

void loop() {
  // Niente nel loop
  Wire.beginTransmission(0x27);  // Inizia la comunicazione con il dispositivo all'indirizzo 0x27
Wire.write("Hello");  // Invia il messaggio "Hello" al dispositivo I2C
Wire.endTransmission();  // Termina la trasmissione

}
