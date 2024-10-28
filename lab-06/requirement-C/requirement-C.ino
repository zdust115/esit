#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define LIGHTSENSOR A0  // A/D Port
const char* ssid = "IoT-UNICA";
const char* password = "I@T-unic@2019";
const char* mqtt_server = "broker.mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int status = 0;
int ledpin = D1;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(ledpin,OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection...");
  WiFi.mode(WIFI_STA);
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
  int ledstatus=0;
  while (!client.connected()) {
    if(millis()-time>200){
      ledstatus = !ledstatus;
      time = millis();
      digitalWrite(ledpin, ledstatus);
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
  if (!client.connected()) reconnect();
  client.loop();
  long now = millis();
  // Send sensor data at each second
  if (now - lastMsg > 500) {
    lastMsg = now;
    int value = analogRead(LIGHTSENSOR);  // read sensor data
    value/=4;
    String msg = "Light level: ";

    switch(value){
      case 0:
        msg+= "light";
      break;
      case 1:
        msg+= "half-light";
      break;
      case 2:
        msg+= "half-dark";
      break;
      default:
        msg+= "dark";
      break;
    }
    msg = msg + value;
    char message[58];
    msg.toCharArray(message, 58);
    Serial.println(message);
    // Publish sensor data to MQTT broker
    client.publish("sensorData", message);
  }
}