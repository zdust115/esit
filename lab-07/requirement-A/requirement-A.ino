#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TM1637Display.h>
#define LIGHTSENSOR A0  // A/D Port


const char* ssid = "IoT-UNICA";
const char* password = "I@T-unic@2019";

const char* mqtt_server = "broker.mqtt-dashboard.com";
const int CLK = D2;  // Set the CLK pin connection to the display
const int DIO = D3;  // Set the DIO pin connection to the display
const int DIMENSIONE_ARRAY = 7;

TM1637Display display(CLK, DIO);
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
String msg;
const int personalId = 7;
uint8_t emptyReset[] = { 0x00, 0x00, 0x00, 0x00 };

int values[7];
bool flags[7];



void setup() {
  Serial.begin(115200);
  delay(3000);
  display.setBrightness(5);
  display.setSegments(emptyReset);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
/*ricezione degli altri valori sul topic*/
void callback(char* topic, byte* payload, unsigned int length) {

  // Converte il payload in una stringa leggibile
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  //esempio mess = ID5,76
  int posizioneVirgola = message.indexOf(',');
  int position = (int)message.charAt(posizioneVirgola - 1);
  position--;  //utilizzo array di dimensione uguale al numero, quindi gli id sono scalati di 1
  int valore = message.substring(posizioneVirgola + 1).toInt();

  values[position] = valore;
  flags[position] = true;

  if (checkFlags()) {
    //gestisci val max
    int idPosMax = posizioneMax();
    valore = values[idPosMax];

    display.setSegments(emptyReset);
    display.showNumberDec(idPosMax + 1, false, 1, 0);  //re-incremento di 1 per avere l'id corretto del dispositivo
    display.showNumberDec(valore, false, 2, 2);        //stampo il valore max

    delay(5000);  //visualizzo per 5 sec

    //reset
    for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
      values[i] = 0;
      flags[0] = false;
    }
  }
}

int posizioneMax() {
  int temp = 0;
  int index = 0;
  for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
    if (temp < values[i]) {
      temp = values[i];
      index = i;
    }
  }
  return index;
}

//rende true se tutte le flag sono true
bool checkFlags() {
  int flag = true;
  for (int i = 0; i < DIMENSIONE_ARRAY; i++) {
    flag = flag && flags[i];
  }
  return flag;
}

void reconnect() {
  int time = millis();
  int ledstatus = 0;
  while (!client.connected()) {
    if (millis() - time > 200) {
      time = millis();
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
    int myvalue = map(analogRead(LIGHTSENSOR), 0, 1024, 0, 99);  // read sensor data, normalizza a 0-99
    msg = "ID7,";                                                //aggiungo al messaggio l'id del dispositivo
    msg = msg + myvalue;
    display.showNumberDec(personalId, false, 1, 0);
    display.showNumberDec(myvalue, false, 2, 2);
    char message[58];
    msg.toCharArray(message, 58);
    Serial.println(message);
    // Publish sensor data to MQTT broker
    client.publish("sensorData", message);
  }
}
