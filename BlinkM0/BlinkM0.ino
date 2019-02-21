/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

// The other leds are controlled with transistors
#define LEDCOUNT  5
int ledPins[LEDCOUNT] = {9, 10, 11, 12, 13};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs
  for (int i = 0; i < LEDCOUNT; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i = 0; i < LEDCOUNT; i++) {
    digitalWrite(ledPins[i], HIGH);   // turn the LEDs on (HIGH is the voltage level)
  }
  delay(1000);               // wait for a second
  
  for (int i = 0; i < LEDCOUNT; i++) {
    digitalWrite(ledPins[i], LOW);    // turn the LED off by making the voltage LOW
  }
  delay(1000);               // wait for a second
}
