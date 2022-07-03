#include "HomeSpan.h"
#include "DEV_stepper.h"

void setup() {
  Serial.println("Setting up device.");
  Serial.begin(115200);

  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  Serial.println("Setting up Bridge");
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 

  LOG1("Setting up Stepper");
  new SpanAccessory();                                                          
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Nom Nom");
    new DEV_Stepper();
}

void loop() {
  // step one revolution in one direction:
  homeSpan.poll();
}
