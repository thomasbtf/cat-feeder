void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(26, OUTPUT);
}

// the code in loop function is executed repeatedly infinitely
void loop() {
  digitalWrite(26, HIGH); // turn the LED on
  delay(1500);             // wait for 500 milliseconds
  digitalWrite(26, LOW);  // turn the LED off
  delay(500);             // wait for 500 milliseconds
}
