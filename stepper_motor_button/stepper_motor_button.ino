#include <ESP8266WiFi.h>
#include <Stepper.h>

//stepper config
const int revolution = 200;                   // Revolution steps
int clockwise = -1;                           // One step clockwise
Stepper stepper(revolution, D1, D2, D5, D6);  // Initialize the stepper library on D1,D2,D5,D6

//variabili pulsante
int buttonPin = 13;  //D7
int buttonStateOld = 0;
int buttonStateNew = 0;


void setup() {
  Serial.begin(115200);       //inizializzo porta seriale
  pinMode(buttonPin, INPUT);  //bottone = input
  stepper.setSpeed(80);       // Set motor speed at 80 rpm
}
void loop() {
  stepper.step(clockwise);
  buttonStateOld = buttonStateNew;
  buttonStateNew = digitalRead(buttonPin);
  // Invert motor direction on button press
  if (buttonStateNew==1 &&buttonStateOld ==0) {
    Serial.println("premuto");
    clockwise *= -1;
  }  
}