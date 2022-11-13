/*Example sketch to control a stepper motor with A4988 stepper motor driver, AccelStepper library and Arduino: continuous rotation. More info: https://www.makerguides.com */

// Include the AccelStepper library:
#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define stepPin 25
#define dirPin 26
#define motorInterfaceType 1

#define enablePin 27
#define ms1Pin 14
#define ms2Pin 12
#define ms3Pin 13

#define steps_per_rotation 200
#define no_of_dis_sections 6


// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void set_full_step(){
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
}

void set_half_step(){
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, LOW);
  digitalWrite(ms3Pin, LOW);
}

void set_quarter_step(){
  digitalWrite(ms1Pin, LOW);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, LOW);
}

void set_eigth_step(){
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, LOW);
}

void set_sixteen_step(){
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, HIGH);
}

void activate_driver_board(){
  digitalWrite(enablePin, LOW);
}

void deactivate_driver_board(){
  digitalWrite(enablePin, HIGH);
}

void setup() {
  Serial.begin(115200);
  // Set the maximum speed in steps per second:
  stepper.setMaxSpeed(6400);
  stepper.setAcceleration(30);

  pinMode(enablePin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);

  set_full_step();
}

void dispense_one_portion(int step_factor){
  // Reset the position to 0:
  stepper.setCurrentPosition(0);

  // Run the motor forward at 400 steps/second until the motor reaches 600 steps (3 revolutions):
  while(stepper.currentPosition() != -steps_per_rotation/no_of_dis_sections*step_factor)
  {
    stepper.setSpeed(-400);
    stepper.runSpeed();
  }
  delay(3000);
}


void loop() { 
  Serial.println("Full step");
  set_full_step();
  dispense_one_portion(1);

  Serial.println("1/2 step");
  set_half_step();
  stepper.setSpeed(-400*2);
  dispense_one_portion(2);

  Serial.println("1/4 step");
  set_quarter_step();
  stepper.setSpeed(-400*4);
  dispense_one_portion(4);

  Serial.println("1/8 step");
  set_eigth_step();
  stepper.setSpeed(-400*8);
  dispense_one_portion(8);

  Serial.println("1/16 step");
  set_sixteen_step();
  stepper.setSpeed(-400*16);
  dispense_one_portion(16);

  Serial.println("Disabeled");
  set_full_step();
  deactivate_driver_board();
  dispense_one_portion(1);
  activate_driver_board();
}
