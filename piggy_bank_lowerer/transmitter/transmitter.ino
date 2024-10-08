#include <RF24.h>

// Replace with your desired RF24 library pins
#define CE_PIN 8
#define CSN_PIN 9

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address for the receiver
const uint8_t address[6] = {0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

// Function to send a control message
void sendControlMessage(bool direction) {
  radio.stopListening();
  uint8_t data = direction ? 1 : 0; // 1 for forward, 0 for backward
  radio.write(&data, sizeof(data));
  radio.startListening();
}

void setup() {
  // Initialize the RF24 module
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
}

void loop() {
  // Replace with your desired input method (e.g., buttons, joystick)
  bool forward = digitalRead(A0); // Example: Read analog input for forward direction
  bool backward = digitalRead(A1); // Example: Read analog input for backward direction

  // Send control message based on input
  if (forward) {
    sendControlMessage(true);
  } else if (backward) {
    sendControlMessage(false);
  }
}