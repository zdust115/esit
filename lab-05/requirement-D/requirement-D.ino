#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// LED pin
int LEDPIN = D1;

// Wi-Fi credentials
const char* ssid = "Wind3 Frau";
const char* password = "4nd1yjynbgoyv0ce";

// MQTT server settings
const char* mqtt_server = "broker.mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);

// LED status and timer variables
int led_status = 0; // 0 = off, 1 = on, 2 = blink
bool isBlinking = false; // To control blinking state
long lastMsg = 0;
char msg[50];
long lastOnTime = 0; // Tracks when LED was last turned on
const long autoOffInterval = 10000; // 10 seconds interval for auto-off

// Blink timing variables
long previousMillis = 0;
const long blinkInterval = 500;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);
  delay(1000); // Delay for serial port readiness
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.println("Attempting WIFI connection...");
  WiFi.mode(WIFI_STA);           // Set to client mode
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
  int readvalue = (char)payload[0] - '0'; // Convert to integer (0, 1, or 2)
  
  switch(readvalue) {
    case 0:
      led_status = 0;
      isBlinking = false;
      break;
    case 1:
      led_status = 1;
      isBlinking = false;
      lastOnTime = millis(); // Start the timer for auto-off
      break;
    case 2:
      led_status = 2;
      isBlinking = true;
      lastOnTime = 0; // Reset timer for blinking mode
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
    digitalWrite(LEDPIN, !digitalRead(LEDPIN)); // Toggle LED
  }
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();  // Process incoming messages

  long now = millis();
  
  // Publish LED status every 5 seconds
  if ((now - lastMsg) > 5000) {
    lastMsg = now;
    snprintf(msg, 75, "LED Status: %ld", led_status);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("LedStatus", msg);
  }

  // Control LED based on led_status
  if (led_status == 1) {
    digitalWrite(LEDPIN, LOW);  // Turn LED on (LOW = ON for active-low LED)
    
    // Check for auto-off after 10 seconds
    if (now - lastOnTime >= autoOffInterval) {
      led_status = 0; // Turn LED off
      digitalWrite(LEDPIN, HIGH); // Turn LED off (HIGH = OFF)
      snprintf(msg, 75, "LED auto-turned off after 10 seconds");
      Serial.println(msg);
      client.publish("LedStatus", msg); // Publish auto-off message
    }
  } else if (led_status == 0) {
    digitalWrite(LEDPIN, HIGH); // Turn LED off
  } else if (led_status == 2 && isBlinking) {
    blink_led(); // Blink LED if in blinking mode
  }
}
