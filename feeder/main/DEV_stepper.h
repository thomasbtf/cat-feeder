#include <Stepper.h>

const int feedingTime = 2000; // in ms
const int stepsPerRevolution = 200;

struct DEV_Stepper : Service::LightBulb {

  Stepper *motor;
  SpanCharacteristic *power;

  DEV_Stepper(int IN1, int IN2, int IN3, int IN4) : Service::LightBulb(){       // constructor() method
    power = new Characteristic::On();
    motor = new Stepper(stepsPerRevolution, IN1, IN2, IN3, IN4);
    motor->setSpeed(100);
  }

  void feed() {
    Serial.println("Feeding...");
    motor->step(350);
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
    Serial.println("---------------------");
    Serial.println("getVal...");
    Serial.println(power->getVal());
    Serial.println("timeVal...");
    Serial.println(power->timeVal());
    if(power->getVal() && power->timeVal() > feedingTime){   // check that power is true, and that time since last modification is greater than 3 seconds 
      power->setVal(false);
    }
  }
};
