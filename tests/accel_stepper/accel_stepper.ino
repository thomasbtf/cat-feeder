// source https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define HALFSTEP  8

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(HALFSTEP, IN1, IN3, IN2, IN4);

void setup() {
  myStepper.setMaxSpeed(1000);
  myStepper.setSpeed(1000);
  //myStepper.setAcceleration(1000);
  myStepper.moveTo(2038);
}

void feed() {
  myStepper.run();
  myStepper.moveTo(myStepper.currentPosition() + 10000);
  delay(500);
  myStepper.moveTo(myStepper.currentPosition() - 10000);
  delay(200);
}

void loop() {
  // Change direction once the motor reaches target position
  //feed();
  myStepper.runSpeed();
}
