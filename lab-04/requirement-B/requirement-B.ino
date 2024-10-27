#include <ESP8266WiFi.h>
#include <Stepper.h>

const int revolution = 200;                   // Steps per revolution
Stepper stepper(revolution, D1, D2, D5, D6);  // Initialize stepper on pins D1, D2, D5, D6
int clockwise = 1;
String command = "A80";  // Command string

void setup() {
  delay(5000);           // Allow time for serial monitor to connect

  // Extract speed and direction from command
  char direction = command.charAt(0);        // Get direction character
  int speed = command.substring(1).toInt();  // Convert string to integer

  stepper.setSpeed(speed);  // Set motor speed

  if (direction == 'A' || direction =='a') {
    clockwise = 1;
  } else {
    clockwise = -1;
  }

 
}

void loop() {
  stepper.step(clockwise);
}
