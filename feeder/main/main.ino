#include "HomeSpan.h"
#include "DEV_stepper.h"

#define stepPin 25
#define dirPin 26
#define enablePin 27

void setup() {
  Serial.begin(115200);
  
  Serial.println("Setting up device.");
  homeSpan.begin(Category::Bridges,"HomeSpan Bridge");

  Serial.println("Setting up Bridge");
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify(); 

  Serial.println("Setting up Stepper");
  new SpanAccessory();                                                          
  new Service::AccessoryInformation();
  new Characteristic::Identify(); 
  new Characteristic::Name("Mampf");
  new DEV_Stepper(stepPin, dirPin, enablePin);
}

void loop() {
  homeSpan.poll();
}
