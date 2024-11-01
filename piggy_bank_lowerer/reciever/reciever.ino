#include <SPI.h>
#include <RF24.h>

// define pins for the radio
#define CE_PIN 8
#define CSN_PIN 9

// define the pin for the motor
#define MOTOR_PIN 3

//define the content to be expected for messages
#define FORWARD 1
#define BACK 0

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Addresses
uint8_t address[][6] = {"trans", "piggy"};

// Function to control the motor based on received message
void controlMotor(bool direction) {
  // Replace with the actual motor control code (its supposed to be 
  // brushless in the end I guess)
  if (direction) {
    // Forward motion
    digitalWrite(MOTOR_PIN, HIGH);
  } else {
    // Backward motion
    digitalWrite(MOTOR_PIN, LOW);
  }
}

void setup() {
  // Begin serial channel for debugging
  Serial.begin(9600);

  // Check to make sure that the rf24 module was initialized succesfully
  if (!radio.begin()) {
    Serial.println(F("radio hardware not responding!"));
    while (1) {} // hold program in infinite loop to prevent subsequent errors
  }

  // Prepare to receive messages args for openReadingPipe are the pipe to open
  // and the address to listen for
  radio.openReadingPipe(1, address[0]);
  radio.startListening();

  // Initialize the motor Pin to output
  //pinMode(MOTOR_PIN, OUTPUT);
  for(int i = 2; i <= 5; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // If there is a message available, read it and do the apporpriate action (forwards
  // or back). If no message is available, do nothing. If there is a message, change the
  // state to the direction given for 200 millis. Then start listening again.

  if (radio.available()) {
    // Set up a variable of a specific size to read the message into
    uint8_t data;

    // Read the message into the data variable. The read variable requires the pointer
    // to the variable to read the messasge into and the size of the size of that place.
    // It is possible that this will not function correctly because there is some
    // weirdness where the size of 'data' must be equal to the size of the message which
    // is received. (see the part on read() in the RF24 docs)
    radio.read(&data, sizeof(data));

    // If the data is FORWARD then direction is true, else the direction is false
    bool direction = data == FORWARD;

    //tell the motor to go in a certain direction
    controlMotor(direction);

    //sleep for 200 millis while the motor does its thing
    delay(200);
  }

  //motor testing
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);

  delay(1000);

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
}