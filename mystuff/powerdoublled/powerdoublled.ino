int ledpin1 = 5;  //SD2(gpio9)
int ledpin2 = 0; //SD3(gpio10)
int button = 4;   //D2(gpio4)
int buttonState = 0;
int ledState=0;
unsigned long lastButtonPressTime = 0;
unsigned long ledOnTime = 0;
unsigned long autoOffDelay = 2000;  // 2 secondi

void setup() {
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(ledpin1, ledState);
  digitalWrite(ledpin2, !ledState);
  Serial.begin(115200);
}
void loop() {
  buttonState = digitalRead(button);
  if (buttonState == 1) {
    
    if (millis() - lastButtonPressTime > 200) {
      ledState = !ledState;  // Cambia stato del LED

      Serial.print("LEd status: ");
      Serial.println(ledState);

      digitalWrite(ledpin1, ledState);

      if (ledState == 1) {
        ledOnTime = millis();  // Memorizza il tempo di accensione del LED
      }

      lastButtonPressTime = millis();  // Aggiorna il tempo dell'ultima pressione
    }    
  }

  if (ledState == 1 && (millis() - ledOnTime >= autoOffDelay)) {
    ledState = 0;
    digitalWrite(ledpin1, LOW);

    Serial.print("LEd status: ");
    Serial.println(ledState);
  }

  digitalWrite(ledpin2, !ledState);
  delay(200);
}