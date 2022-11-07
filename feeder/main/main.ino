#include "HomeSpan.h"
#include "DEV_stepper.h"

// ULN2003 Motor Driver Pins
const int IN1 = 14;
const int IN2 = 27;
const int IN3 = 26;
const int IN4 = 25;


void setup() {
  Serial.println("Setting up device.");
  Serial.begin(115200);

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
  new DEV_Stepper(IN1, IN2, IN3, IN4);
}

void loop() {
  homeSpan.poll();
}
