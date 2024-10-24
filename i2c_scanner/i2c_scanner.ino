#include <Wire.h>

void setup() {
  Wire.begin(D2, D1);  // SDA, SCL (D2 -> SDA, D1 -> SCL)
  Serial.begin(115200);
  Serial.println("I2C Scanner avviato");
}

void loop() {
  Serial.println("\nScansione I2C in corso...");
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo I2C trovato all'indirizzo: 0x");
      Serial.println(address, HEX);
    }
  }
  
  // Pausa di 5 secondi prima di ripetere la scansione
  delay(5000);  // 5000 millisecondi = 5 secondi
}
