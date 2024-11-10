#include <ESP8266WiFi.h>

// Rete e password
const char* SSID = "Wind3 Frau";
const char* PASSWORD = "4nd1yjynbgoyv0ce";

void setup() {
  Serial.begin(115200);
  delay(5000);  // Breve ritardo per assicurarsi che Serial sia pronto
  
  Serial.println();
  Serial.print("Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  
  setup_wifi();
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Codice principale da eseguire continuamente
}

void setup_wifi() {
  delay(10);
  Serial.println("Tentativo di connessione a WIFI...");
  
  WiFi.mode(WIFI_STA);           // Modalità stazione (client)
  WiFi.begin(SSID, PASSWORD);     // Avvia la connessione

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");            // Stampa punti come indicatore di attesa
  }
  Serial.println("\nWi-Fi connesso!");
}
