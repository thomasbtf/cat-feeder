//source https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/
//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;
const int rot_speed = 20;

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(rot_speed);
  myStepper.step(100);
  myStepper.step(-100);
  delay(1000);
}
