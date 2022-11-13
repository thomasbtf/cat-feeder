#include <AccelStepper.h>

#define maxFeedingTime 2000 // in ms

// motor characteristics
#define motorInterfaceType 1
#define stepsPerRotation 200
#define noSections 6
#define stepMode 1 // 1 - full step; 2 - half steps; etc..
#define stepsForOnePortion stepsPerRotation/noSections*stepMode

struct DEV_Stepper : Service::LightBulb {

  int ePin;
  SpanCharacteristic *power;
  AccelStepper *motor;

  DEV_Stepper(int stepPin, int dirPin, int enablePin) : Service::LightBulb(){       // constructor() method
    ePin = enablePin;
    power = new Characteristic::On();
    motor = new AccelStepper(motorInterfaceType, stepPin, dirPin);
    motor->setMaxSpeed(1000);
    pinMode(ePin, OUTPUT);
    pinMode(ePin, LOW);
  }
  
  void activate_driver_board(){
    digitalWrite(ePin, LOW);
  }
  
  void deactivate_driver_board(){
    digitalWrite(ePin, HIGH);
  }

  void feed() {
    Serial.println("Feeding...");

    activate_driver_board();
    
    // Reset the position to 0:
    motor->setCurrentPosition(0);
    motor->setSpeed(-100);
  
    // Run the motor forward at 400 steps/second
    while(motor->currentPosition() != -stepsForOnePortion | power->timeVal() > maxFeedingTime)
    {
      motor->runSpeed();
    }

    deactivate_driver_board();

    power->setVal(false);
    
    Serial.println("Done Feeding!");
  }

  boolean update(){
    if(power->getNewVal()){
      feed();
    }
    return(true);
  }
 
  void loop(){
    if(power->getVal() && power->timeVal() > maxFeedingTime){   // check that power is true, and that time since last modification is greater than 3 seconds 
      power->setVal(false);
    }
  }
};
