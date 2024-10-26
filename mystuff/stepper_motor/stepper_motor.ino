#include <ESP8266WiFi.h>
#include <Stepper.h>


const int revolution = 200;                   // Revolution steps
int clockwise = -1;                           // One step clockwise
int steps = 0;                                // Steps counter
Stepper stepper(revolution, D1, D2, D5, D6);  // Initialize the stepper library on D1,D2,D5,D6
void setup() {
  stepper.setSpeed(80);  // Set motor speed at 80 rpm
}
void loop() {
  steps++;
  stepper.step(clockwise);  // Move motor
  if (steps > 2000) {
    clockwise *= -1;
    steps = 0;
  }  // Invert motor direction
}