#define LED1 5          // D1(gpio5)
#define LED2 4          // D2(gpio4)
#define LIGHTSENSOR A0  // A/D Port
int ledstate1 = 0;
int ledstate2 = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(115200);
  while (!Serial);
}
void loop() {
  int value = analogRead(LIGHTSENSOR);
  delay(1000);
  Serial.println(value);
  if (value < 512) {
      digitalWrite(LED1,LOW);
    if(value < 256){
      //00
      digitalWrite(LED2,LOW);
    }else{
      //01
      digitalWrite(LED2,HIGH);

    }

  } else {
      digitalWrite(LED1,HIGH);
    if(value < 768){
      //10
      digitalWrite(LED2,LOW);

    }else{
      //11
      digitalWrite(LED2,HIGH);
    }
  }
}