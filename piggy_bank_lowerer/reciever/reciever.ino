#include <RF24.h>

// Replace with your desired RF24 library pins
#define CE_PIN 8
#define CSN_PIN 9

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address for the transmitter
const uint8_t address[6] = {0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

// Function to control the motor based on received message
void controlMotor(bool direction) {
  // Replace with your actual motor control code
  if (direction) {
    // Forward motion
    digitalWrite(motorPin, HIGH);
  } else {
    // Backward motion
    digitalWrite(motorPin, LOW);
  }
}

void setup() {
  // Initialize the RF24 module
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    uint8_t data;
    radio.read(&data, sizeof(data));
    bool direction = data == 1;
    controlMotor(direction);
  }
}