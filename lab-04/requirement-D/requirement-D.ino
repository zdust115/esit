#include <ESP8266WiFi.h>
#include <Stepper.h>
int button = D7;
int oldvalue = 0;
int value = 0;
int clickcounter = 0;

const int revolution = 200;                   // Revolution steps
int clockwise = -1;                           // One step clockwise
Stepper stepper(revolution, D1, D2, D5, D6);  // Initialize the stepper library on D1,D2,D5,D6
void setup() {
  stepper.setSpeed(80);  // Set motor speed at 80 rpm
  pinMode(button, INPUT);
}
void loop() {
  oldvalue = value;
  value = digitalRead(button);
  if (value == 1 && oldvalue == 0) clickcounter++;
  switch(clickcounter){
    case 1:
      clockwise= -1;
      break;
    
    case 2:
      clockwise=1;
      break;

    default:
      clockwise=0;
      clickcounter=0;
      break;
  }
  stepper.step(clockwise);  // Move motor

}