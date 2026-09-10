#include <PMW3389.h> // Include the header file for the PMW3389 class
#include <USB.h> // Include the header file for the Arduino Mouse library
#include <USBHIDMouse.h> // Include the header file for the Arduino Mouse library

USBHIDMouse Mouse; // Create an instance of the Arduino Mouse library

#define NCS_PIN 3 // Define the chip select pin for the PMW3389 sensor
#define SCK_PIN 8 // Define the clock pin for the PMW3389 sensor
#define MISO_PIN 9 // Define the master in slave out pin for the PMW3389 sensor
#define MOSI_PIN 10 // Define the master out slave in pin for the PMW3389 sensor

#define LC_PIN 1 // Define the pin for the mouse button
#define RC_PIN 2 // Define the pin for the mouse button
#define MC_PIN 7 // Define the pin for the mouse button
#define Rot_A_PIN 6 // Define the pin for the rotary encoder
#define Rot_B_PIN 0 // Define the pin for the rotary encoder

#define DEBOUNCE_DELAY 5 // Define the debounce delay for button presses in milliseconds

PMW3389 sensor(NCS_PIN); // Create an instance of the PMW3389 class with chip select pin 10

struct ButtonState {
  uint8_t pin; // Pin number for the button
  bool lastRead; // Last read state of the button
  bool stableState; // Stable state of the button
  unsigned long lastChangeTime; // Last time the button state changed
};

volatile int8_t scroll = 0; // Variable to hold the position of the rotary encoder

ButtonState buttons[] = {
  {LC_PIN, HIGH, HIGH, 0}, // Initialize the left click button state
  {MC_PIN, HIGH, HIGH, 0},// Initialize the middle click button state
  {RC_PIN, HIGH, HIGH, 0} // Initialize the right click button state
};

void sendMouseMovement(int16_t dx, int16_t dy); // Function prototype for sending mouse movement
void updateButton(ButtonState &button, uint8_t mouseButton); // Function prototype for updating button state

void IRAM_ATTR encoderISR(); // Function prototype for the rotary encoder interrupt service routine

void setup() {
  pinMode(LC_PIN, INPUT_PULLUP); // Set pin 1 as an input with an internal pull-up resistor
  pinMode(RC_PIN, INPUT_PULLUP); // Set pin 2 as an input with an internal pull-up resistor
  pinMode(MC_PIN, INPUT_PULLUP); // Set pin 7 as an input with an internal pull-up resistor
  pinMode(Rot_A_PIN, INPUT_PULLUP); // Set pin 6 as an input with an internal pull-up resistor
  pinMode(Rot_B_PIN, INPUT_PULLUP); // Set pin 0 as an input with an internal pull-up resistor
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  if (!sensor.begin(SCK_PIN, MISO_PIN, MOSI_PIN)) { // Initialize the PMW3389 sensor and check if it was successful
    while(1); // Stop execution if sensor initialization fails
  }
  Mouse.begin(); // Initialize the Arduino Mouse library
  USB.begin(); // Initialize the USB library

  sensor.setDPI(800); // Set the DPI of the PMW3389 sensor to 800
  attachInterrupt(digitalPinToInterrupt(Rot_A_PIN), encoderISR, CHANGE); // Attach an interrupt to the rotary encoder pin A
}

void loop() {
  PMW3389_Motion motion = sensor.readMotion(); // Read motion data from the PMW3389 sensor
  if (motion.isMotion) { // Check if motion was detected
    sendMouseMovement(motion.dx, motion.dy); // Send mouse movement based on the motion data
  }
  updateButton(buttons[0], MOUSE_LEFT); // Update the state of the left click button
  updateButton(buttons[1], MOUSE_MIDDLE); // Update the state of the middle click button
  updateButton(buttons[2], MOUSE_RIGHT); // Update the state of the right click button
  noInterrupts();
  int8_t scrollAmount = scroll;
  scroll = 0;
  interrupts();
  if (scrollAmount != 0) {
    Mouse.move(0, 0, scrollAmount);
}
}

void sendMouseMovement(int16_t dx, int16_t dy) {
  while (dx != 0 || dy != 0) { // Continue sending mouse movement until both dx and dy are zero
    int8_t moveX = constrain(dx, -127, 127); // Constrain dx to the range of -127 to 127
    int8_t moveY = constrain(dy, -127, 127); // Constrain dy to the range of -127 to 127
    Mouse.move(moveX, moveY); // Move the mouse by the constrained values
    dx -= moveX; // Decrease dx by the amount moved
    dy -= moveY; // Decrease dy by the amount moved
  }
}

void updateButton(ButtonState &button, uint8_t mouseButton) {
  bool currentRead = digitalRead(button.pin); // Read the current state of the button
  if (currentRead != button.lastRead) { // Check if the button state has changed
    button.lastChangeTime = millis(); // Update the last change time to the current time
  }
  if ((millis() - button.lastChangeTime) > DEBOUNCE_DELAY) {
    if (currentRead != button.stableState) { // Check if the stable state has changed
      button.stableState = currentRead; // Update the stable state to the current read
      if (button.stableState == LOW) { 
        Mouse.press(mouseButton); // Call the mouse press function if the button is pressed
      } else {
        Mouse.release(mouseButton); // Call the mouse release function if the button is released
      }
    }
  }
  button.lastRead = currentRead; // Update the last read state to the current read
}

void IRAM_ATTR encoderISR() {
  bool aState = digitalRead(Rot_A_PIN); // Read the state of the rotary encoder pin A
  bool bState = digitalRead(Rot_B_PIN); // Read the state of the rotary encoder pin B
  if (aState != bState) { // Check if the states of the encoder pins are different
    scroll++; // Increment the scroll value if the states are different
  } else {
    scroll--; // Decrement the scroll value if the states are the same
  }
}