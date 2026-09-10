#ifndef PMW3389_H
#define PMW3389_H

#include <Arduino.h>
#include <SPI.h>

#define REG_PRODUCT_ID 0x00
#define REG_REVISION_ID 0x01
#define REG_MOTION 0x02
#define REG_DELTA_X_L 0x03
#define REG_DELTA_X_H 0x04
#define REG_DELTA_Y_L 0x05
#define REG_DELTA_Y_H 0x06

struct PMW3389_Motion { // Structure to hold motion data from the PMW3389 sensor because you cant return multiple values from a function
    bool isMotion;
    int16_t dx;
    int16_t dy;
    uint8_t squal;
};

class PMW3389 {
    public:
        PMW3389(uint8_t ncsPin);

        bool begin(int8_t sckPin, int8_t misoPin, int8_t mosiPin);
        
        bool uploadSROM();
        uint8_t readRegister(uint8_t regAddr);
        void writeRegister(uint8_t regAddr, uint8_t value);
        PMW3389_Motion readMotion();
        void setDPI(uint16_t dpi);
        uint16_t getDPI();
    private:
        uint8_t _ncsPin;
        bool _inBurst = false;
        unsigned long _lastBurstTime = 0;
};

#endif