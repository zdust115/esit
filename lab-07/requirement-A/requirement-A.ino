#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TM1637Display.h>
#define LIGHTSENSOR A0  // A/D Port


const char* ssid = "IoT-UNICA";
const char* password = "I@T-unic@2019";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int CLK = D2; // Set the CLK pin connection to the display
const int DIO = D3; // Set the DIO pin connection to the display

TM1637Display display(CLK, DIO);
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
String msg;
int value = 0;
int personalId = 7;
uint8_t emptyReset[] = {0x00, 0x00, 0x00, 0x00};


void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LIGHTSENSOR, INPUT);
  display.setBrightness(5);
  display.setSegments(emptyReset);  
  //setup_wifi();
  //client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);
}
void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("WiFi connected");
}
void callback(char* topic, byte* payload, unsigned int length) {}

void reconnect() {
  int time = millis();
  int ledstatus = 0;
  while (!client.connected()) {
    if (millis() - time > 200) {
      ledstatus = !ledstatus;
      time = millis();
      //digitalWrite(ledpin, ledstatus);
    }

    Serial.println("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.print("clientID: ");
      Serial.println(clientId);
      Serial.println("connected");
      client.subscribe("rxData");
    } else delay(6000);
  }
}
void loop() {
  /* if (!client.connected()) reconnect();
  client.loop(); */
  long now = millis();
  // Send sensor data at each second
  if (now - lastMsg > 500) {
    lastMsg = now;
    int value = map(analogRead(LIGHTSENSOR),0,1024,0,99);  // read sensor data, normalizza a 0-99
    msg= "ID7,";
    msg = msg + value;
    display.showNumberDec(personalId,false,1,0);
    display.showNumberDec(value,false,2,2);
    char message[58];
    msg.toCharArray(message, 58);
    Serial.println(message);
    // Publish sensor data to MQTT broker
    client.publish("sensorData", message);
  }
}

