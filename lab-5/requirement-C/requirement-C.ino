#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//const char* ssid = "IoT-UNICA";
//const char* password = "I@T-unic@2019";

int LEDPIN = D1;

// Rete e password casa
const char* ssid = "Wind3 Frau";
const char* password = "4nd1yjynbgoyv0ce";

const char* mqtt_server = "broker.mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int led_status = 0; // 0 = off, 1 = on, 2 = blink
int readvalue;
bool isBlinking = false; // To control blinking state
long previousMillis = 0; // For timing LED blink
const long blinkInterval = 500; // Interval for LED blink in milliseconds

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(1000); //delay per attendere la porta seriale
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection...");

  WiFi.mode(WIFI_STA);           // Modalità stazione (client)
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }
  Serial.println("WiFi connected");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Read payload and set led_status
  readvalue = (char)payload[0] - '0'; // Convert character to integer (0, 1, or 2)
  
  switch(readvalue) {
    case 0:
    case 1:
      led_status = readvalue;
      isBlinking = false; // Stop blinking
      break;
    case 2:
      led_status = 2;
      isBlinking = true; // Start blinking
      break;
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("LedStatus", "LED Status");
      client.subscribe("LedDrive");
    } else {
      Serial.print(".");
      delay(6000);
    }
  }
}

void blink_led() {
  long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    // Toggle LED state
    if (digitalRead(LEDPIN) == LOW) {
      digitalWrite(LEDPIN, HIGH);  // Turn LED off
    } else {
      digitalWrite(LEDPIN, LOW);   // Turn LED on
    }
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();  // Process incoming messages

  long now = millis();
  if ((now - lastMsg) > 5000) {
    lastMsg = now;
    snprintf(msg, 75, "LED Status: %ld", led_status);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("LedStatus", msg);
  }

  // Change LED status based on led_status value
  if (led_status == 1) {
    digitalWrite(LEDPIN, LOW);  // LED on by making the voltage LOW
  } else if (led_status == 0) {
    digitalWrite(LEDPIN, HIGH); // LED off by making the voltage HIGH
  } else if (led_status == 2 && isBlinking) {
    blink_led();  // Call blink function if LED is in blinking mode
  }
}
