#include <Arduino.h>
#include <SPI.h>
#include <BleMouse.h>
#include "PMW3389_ESP32.h"

BleMouse Mouse("blootoof dewice is redy to pear", "sharc !!", 100);

// XIAO ESP32 Pin Definitions
#define NCS_PIN   D3
#define SCK_PIN   D8
#define MISO_PIN  D9
#define MOSI_PIN  D10

#define LC_PIN    D1
#define RC_PIN    D2
#define MC_PIN    D7
#define Rot_A_PIN D6
#define Rot_B_PIN D0

#define DEBOUNCE_DELAY 5

PMW3389_ESP32 sensor(NCS_PIN);

struct ButtonState {
  uint8_t pin;
  bool lastRead;
  bool stableState;
  unsigned long lastChangeTime;
};

volatile int8_t scroll = 0;

ButtonState buttons[] = {
  {LC_PIN, HIGH, HIGH, 0},
  {MC_PIN, HIGH, HIGH, 0},
  {RC_PIN, HIGH, HIGH, 0}
};

void sendMouseMovement(int16_t dx, int16_t dy);
void updateButton(ButtonState &button, uint8_t mouseButton);
void IRAM_ATTR encoderISR();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Starting Boot Sequence ---");

  // Configure GPIO inputs
  pinMode(LC_PIN, INPUT_PULLUP);
  pinMode(RC_PIN, INPUT_PULLUP);
  pinMode(MC_PIN, INPUT_PULLUP);
  pinMode(Rot_A_PIN, INPUT_PULLUP);
  pinMode(Rot_B_PIN, INPUT_PULLUP);

  // Initialize Chip Select line explicitly
  pinMode(NCS_PIN, OUTPUT);
  digitalWrite(NCS_PIN, HIGH);

  // Explicitly initialize SPI hardware bus on XIAO pins
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, NCS_PIN);
  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.println("Initializing PMW3389 Sensor...");
  if (!sensor.begin(SCK_PIN, MISO_PIN, MOSI_PIN)) {
    Serial.println("WARNING: PMW3389 Sensor Init Failed! Check SPI wiring.");
  } else {
    Serial.println("PMW3389 Sensor OK!");
    sensor.setDPI(800);
  }

  attachInterrupt(digitalPinToInterrupt(Rot_A_PIN), encoderISR, CHANGE);

  Serial.println("Starting BLE Mouse Stack...");
  Mouse.begin();
  Serial.println("BLE Mouse Started! Search for 'blootoof dewice is redy to pear' on your PC.");
}

void loop() {
  if (Mouse.isConnected()) {
    PMW3389_Motion motion = sensor.readMotion();
    if (motion.isMotion) {
      sendMouseMovement(motion.dx, motion.dy);
    }
    
    updateButton(buttons[0], MOUSE_LEFT);
    updateButton(buttons[1], MOUSE_MIDDLE);
    updateButton(buttons[2], MOUSE_RIGHT);
    
    noInterrupts();
    int8_t scrollAmount = scroll;
    scroll = 0;
    interrupts();
    
    if (scrollAmount != 0) {
      Mouse.move(0, 0, scrollAmount);
    }
    // Removed delay(1) to maximize polling frequency and eliminate input lag
  } else {
    delay(10);
  }
}

void sendMouseMovement(int16_t dx, int16_t dy) {
  int8_t moveX = constrain(dx, -127, 127);
  int8_t moveY = constrain(dy, -127, 127);
  Mouse.move(moveX, moveY);
}

void updateButton(ButtonState &button, uint8_t mouseButton) {
  bool currentRead = digitalRead(button.pin);
  if (currentRead != button.lastRead) {
    button.lastChangeTime = millis();
  }
  if ((millis() - button.lastChangeTime) > DEBOUNCE_DELAY) {
    if (currentRead != button.stableState) {
      button.stableState = currentRead;
      if (button.stableState == LOW) { 
        Mouse.press(mouseButton);
      } else {
        Mouse.release(mouseButton);
      }
    }
  }
  button.lastRead = currentRead;
}

void IRAM_ATTR encoderISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  
  // Software debounce for rotary encoder (5ms filter)
  if (interruptTime - lastInterruptTime > 5) {
    bool aState = digitalRead(Rot_A_PIN);
    bool bState = digitalRead(Rot_B_PIN);
    if (aState != bState) {
      scroll++;
    } else {
      scroll--;
    }
    lastInterruptTime = interruptTime;
  }
}