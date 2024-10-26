#include <ESP8266WiFi.h>

//const char* SSID = "IoT-UNICA";
//const char* PASSWORD = "I@T_unic@2019";

const char* SSID = "Wind3Frau";
const char* PASSWORD = "4nd1yjynbgoyv0ce";


void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(10000);
  Serial.println();
  Serial.println("Mac: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  WiFi.mode(WIFI_STA);
  setup_wifi();
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}

void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
  }
  Serial.println("Wi-Fi connected!");
}
