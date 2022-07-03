#include <Stepper.h>

const int feedingTime = 3000; // in ms
const int stepsPerRevolution = 2038;

// ULN2003 Motor Driver Pins
const int IN1 = 19;
const int IN2 = 18;
const int IN3 = 5;
const int IN4 = 17;

Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

struct DEV_Stepper : Service::LightBulb {
 
  SpanCharacteristic *power;

  DEV_Stepper() : Service::LightBulb(){       // constructor() method
    power=new Characteristic::On();
    myStepper.setSpeed(5);
  }

  void feed() {
    Serial.println("Feeding...");
    myStepper.step(stepsPerRevolution);
  }

  boolean update(){
    Serial.println("Got update!");
    Serial.println(power->getNewVal());
    if(power->getNewVal()){
      feed();
    }
    return(true);
  }
 
  void loop(){
    if(power->getVal() && power->timeVal() > feedingTime){   // check that power is true, and that time since last modification is greater than 3 seconds 
      power->setVal(false);
    }
  }
};
