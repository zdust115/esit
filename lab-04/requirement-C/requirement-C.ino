#include <ESP8266WiFi.h>
#include <Stepper.h>

const int revolution = 200;                   // Steps per revolution
Stepper stepper(revolution, D1, D2, D5, D6);  // Initialize stepper on pins D1, D2, D5, D6
int clockwise = 1;
int speed = 80; //default speed for step case
String command = "s80";  // Command string

void setup() {
  delay(5000);  // Allow time for serial monitor to connect

  // Extract speed and direction from command
  char direction = command.charAt(0);        // Get direction character


  if (direction == 'S' || direction == 's') {
    //step case, do steps and stop
    stepper.setSpeed(speed);  // Set motor speed at default
    Serial.println("stepping");
    stepper.step(command.substring(1).toInt()); //use speed as steps in step case
    delay(99999);
  } else {
    speed = command.substring(1).toInt();
    stepper.setSpeed(speed);  // Set motor speed only if specify direction
    if (direction == 'A' || direction == 'a') {
      clockwise = 1;
    } else {
      clockwise = -1;
    }
  }
}

void loop() {
  stepper.step(clockwise);
}
