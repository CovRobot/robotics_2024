#include <SPI.h>
#include <RF24.h>

// Replace with your desired RF24 library pins
#define CE_PIN 8
#define CSN_PIN 9

// Pins for the joystick
#define JOY_X A0
#define JOY_Y A1

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Addresses
uint8_t address[][6] = {"00001", "00010"};

void setup() {
  // Begin serial channel for debugging
  Serial.begin(9600);

  // Check to make sure that the rf24 module was initialized succesfully
  if (!radio.begin()) {
    Serial.println(F("radio hardware not responding!"));
    while (1) {} // hold program in infinite loop to prevent subsequent errors
  }

  // prepare to send messages from address[0] on pipe 0 by default
  radio.openWritingPipe(address[0]);
}

void loop() {
  // send the current data from the joystick to the car

  // read in the data from the joystick
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
}