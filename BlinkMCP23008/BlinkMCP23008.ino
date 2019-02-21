#include <Wire.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly, 
  using the I2C controlled IO expander MCP23008.
 
 */

// The off-board leds are controlled with transistors set
// using the following digital pins.

#define LEDCOUNT  4
int ledPins[LEDCOUNT] = {9, 10, 11, 12};

#define ioExtenderAddress 0x20
 
#define ioExtenderRegisterCount 11

byte ioExtenderRegisterSetup[ioExtenderRegisterCount] = {
  0,  // 00 IODIR   All pins are outputs
  0,  // 01 IPOL    All pins used as inputs have normal polarity
  0,  // 02 GPINTEN None of the pins are used for interrupt on change 
  0,  // 03 DEFVAL  Default comparison values not needed 
  0,  // 04 INTCON  Comparison type not needed
  0,  // 05 IOCON   Sequential op enabled (ie, register pointer increments)
  0,  // 06 GPPU    Pull-up resistors not used for output pins 
  0,  // 07 INTF    Interrupt flags (Read only) 
  0,  // 08 INTCAP  Interrupt data capture (Read only) 
  0,  // 09 GPIO    Clear all the output pins and thus the output latch bits
  0   // 0A OLAT    Clear all the output latch bits and thus the output pins
};
#define GPIO 0x9
#define OLAT 0xA

// the setup routine runs once when you press reset:

void setup() {                

  // Establish the connection to the io extender

  Wire.begin();         // Join the bus as master
  
  Wire.beginTransmission(ioExtenderAddress);
  Wire.write((byte)0x00);                                           // register addressing starts at 0
  Wire.write(ioExtenderRegisterSetup, ioExtenderRegisterCount);     // sends one byte for each device register
  Wire.endTransmission();    // stop transmitting

  // initialize the digital pins as outputs

  pinMode(LED_BUILTIN, OUTPUT);
  
}

// the loop routine runs over and over again forever:

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  Wire.beginTransmission(ioExtenderAddress);
  Wire.write((byte)OLAT);     // output pins
  Wire.write((byte)0xFF);     // set
  Wire.endTransmission();

  delay(1000);                // wait for a second
  
  digitalWrite(LED_BUILTIN, LOW);
  
  Wire.beginTransmission(ioExtenderAddress);
  Wire.write((byte)OLAT);     // output pins
  Wire.write((byte)0x00);     // clear
  Wire.endTransmission();
  
  delay(1000);                // wait for a second
}
