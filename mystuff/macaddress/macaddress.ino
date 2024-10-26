#include <ESP8266WiFi.h>

const char* ssid = "IoT-UNICA";
const char* password = "I@T-unic@2019";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //imposto il canale seriale
  delay(3000);
  Serial.println();
  Serial.print("MAC Address of the board: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  setup_wifi();
  Serial.println();
  Serial.println("IP adddress:");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection ...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("WiFi connected");
  delay(10);
}