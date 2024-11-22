#include <SPI.h>
#include <RF24.h>

// Replace with your desired RF24 library pins
#define CE_PIN 8
#define CSN_PIN 9

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Addresses
uint8_t address[][6] = {"trans", "piggy"};

//defined content options for the messages from this system to the pulley system
#define FORWARD 1
#define BACK 0

// Function to send a control message
void sendControlMessage(byte message) {
  // Send the message using the write function. Arguments for the write function are
  // a pointer to the message and the length of the message
  radio.write(&message, sizeof(message));
}

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
  // Send messages indicating direction to the pulley system. The system will
  // receive those messages and move like 200 millis when it gets a direction.
  // Otherwise it won't do anything.


  // Replace with your desired input method (e.g., buttons, joystick)
  int forward = analogRead(A0); // Example: Read analog input for forward direction
  if (forward<340){
    sendControlMessage(FORWARD);
  }
  else if (forward>680){
    sendControlMessage(BACK);
  } 
}