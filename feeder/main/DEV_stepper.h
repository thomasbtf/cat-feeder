#include <Stepper.h>

const int feedingTime = 3000; // in ms
const int stepsPerRevolution = 2038;

// ULN2003 Motor Driver Pins
//const int IN1 = 19;
//const int IN2 = 18;
//const int IN3 = 5;
//const int IN4 = 17;

// Stepper myStepper = Stepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

struct DEV_Stepper : Service::LightBulb {

  Stepper *myStepper;
  SpanCharacteristic *power;

  DEV_Stepper(int IN1, int IN2, int IN3, int IN4) : Service::LightBulb(){       // constructor() method
    power = new Characteristic::On();
    myStepper = new Stepper(stepsPerRevolution, IN1, IN3, IN2, IN4);
    myStepper->setSpeed(15);
  }

  void feed() {
    Serial.println("Feeding...");
    myStepper->step(stepsPerRevolution);
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
