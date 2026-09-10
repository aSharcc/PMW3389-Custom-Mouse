    #include "PMW3389.h" // Include the header file for the PMW3389 class 
    #include "utility/PMW3389_Srom.h" // Include the header file for the PMW3389 SROM data

    PMW3389::PMW3389(uint8_t ncsPin) {
        _ncsPin = ncsPin; // Defines the private chip select pin for the PMW3389 sensor
    }

    bool PMW3389::begin(int8_t sckPin, int8_t misoPin, int8_t mosiPin) {
        pinMode(_ncsPin, OUTPUT); // Set the chip select pin as an output on arduino
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        SPI.begin(sckPin, misoPin, mosiPin, _ncsPin); // Initialize the SPI library with the specified pins
        writeRegister(0x3B, 0xB6); // Write 0xB6 to the power up reset register to reset the PMW3389 sensor
        delay(50); // Wait for 50 milliseconds for chip to reboot
        // Ensure SPI is in a known state by toggling the chip select pin
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        delayMicroseconds(40); // Wait for 40 microseconds
        digitalWrite(_ncsPin, LOW); // Set the chip select pin low to start communication with the PMW3389 sensor
        delayMicroseconds(40); // Wait for 40 microseconds
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        return uploadSROM(); // Call the uploadSROM function to upload the SROM data to the PMW3389 sensor
    }

    bool PMW3389::uploadSROM() {
        writeRegister(0x10, 0x20); // Disables rest mode
        writeRegister(0x3A, 0x5A); // Resets the PMW3389 sensor
        delay(50); // Wait for 50 milliseconds for chip to reboot
        readRegister(0x02); // Read the motion register to clear it
        readRegister(0x03); // read the delta x low register to clear it
        readRegister(0x04); // read the delta x high register to clear it
        readRegister(0x05); // read the delta y low register to clear it
        readRegister(0x06); // read the delta y high register to clear it
        writeRegister(0x13, 0x1D); // Arms the SROM download
        delay(10); // Wait for 10 milliseconds for the PMW3389 sensor to arm the SROM download
        writeRegister(0x13, 0x18); // Starts the SROM download state
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE3)); // Start an SPI transaction with a clock speed of 2 MHz, MSB first, and SPI mode 3
        digitalWrite(_ncsPin, LOW); // Set the chip select pin low to start communication with the PMW3389 sensor
        SPI.transfer(0x62 | 0x80); // Set MSB to 1 to indicate a write operation and send the Register address to write to (0x62)
        delayMicroseconds(15); // Wait for 15 microseconds to allow the PMW3389 sensor to process the request
        for (uint16_t i = 0; i < 4094; i++) {
            SPI.transfer(PMW3389_SROM[i]); // Send the SROM data to the PMW3389 sensor, reading each byte from program memory
            delayMicroseconds(15); // Wait for 15 microseconds to allow the PMW3389 sensor to process the request
        }
        delayMicroseconds(2); 
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        SPI.endTransaction(); // End the SPI transaction
        delayMicroseconds(200); // Wait for 200 microseconds to allow the PMW3389 sensor to process the request
        readRegister(0x2A); // Read the SROM_ID register to verify that the SROM upload was successful
        if (readRegister(0x00) != 0x47) // Read the product ID register to verify that the PMW3389 sensor is responding correctly
            return false; // Return false if the product ID is not correct
        writeRegister(0x10, 0x00); // Write 0x00 to the config2 register to set the PMW3389 sensor to normal operation mode
        return true; // Return true if the SROM upload was successful and the product ID is correct
    }

    uint8_t PMW3389::readRegister(uint8_t regAddr) {
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE3)); // Start an SPI transaction with a clock speed of 2 MHz, MSB first, and SPI mode 3
        digitalWrite(_ncsPin, LOW); // Set the chip select pin low to start communication with the PMW3389 sensor
        SPI.transfer(regAddr & 0x7F); // Send the register address to read from, with the MSB set to 0 to indicate a read operation
        delayMicroseconds(160); // Wait to allow the PMW3389 sensor to process the request
        uint8_t data = SPI.transfer(0x00); // Recieve the data from the PMW3389 sensor by sending a dummy byte (0x00)
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        SPI.endTransaction(); // End the SPI transaction
        delayMicroseconds(20); // 
        return data; // Return the data read from the PMW3389 sensor
    }

    void PMW3389::writeRegister(uint8_t regAddr, uint8_t value) {
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE3)); // Start an SPI transaction with a clock speed of 2 MHz, MSB first, and SPI mode 3
        digitalWrite(_ncsPin, LOW); // Set the chip select pin low to start communication with the PMW3389 sensor
        SPI.transfer(regAddr | 0x80); // Send the register address to write to, with the MSB set to 1 to indicate a write operation
        SPI.transfer(value); // Send the value to write to the PMW3389 sensor
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        SPI.endTransaction(); // End the SPI transaction
        delayMicroseconds(180); // 
    }

    PMW3389_Motion PMW3389::readMotion() {
        PMW3389_Motion result; // Create a PMW3389_Motion struct to hold the motion data
        if (!_inBurst || (millis() - _lastBurstTime > 500)) {
            _inBurst = true; // Set the _inBurst flag to true to indicate that a burst read is in progress
            _lastBurstTime = millis(); // Update the last burst time to the current time
            writeRegister(0x50, 0x00); // Write 0x00 to the motion burst register to start a motion burst read
        }
        SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE3)); //  Start an SPI transaction with a clock speed of 2 MHz, MSB first, and SPI mode 3
        digitalWrite(_ncsPin, LOW); // Set the chip select pin low to start communication with the PMW3389 sensor
        SPI.transfer(0x50 & 0x7F); // Send the register address to read from, with the MSB set to 0 to indicate a read operation
        delayMicroseconds(35); // Wait to allow the PMW3389 sensor to process the request
        uint8_t motion = SPI.transfer(0x00); // Recieve the motion data from the PMW3389 sensor by sending a dummy byte (0x00)
        SPI.transfer(0x00); // Send a dummy byte to read the observation byte and discard it
        uint8_t deltaX_L = SPI.transfer(0x00); // Recieve the delta X low byte from the PMW3389 sensor by sending a dummy byte (0x00)
        uint8_t deltaX_H = SPI.transfer(0x00); // Recieve the delta X high byte from the PMW3389 sensor by sending a dummy byte (0x00)
        uint8_t deltaY_L = SPI.transfer(0x00); // Recieve the delta Y low byte from the PMW3389 sensor by sending a dummy byte (0x00)
        uint8_t deltaY_H = SPI.transfer(0x00); // Recieve the delta Y high byte from the PMW3389 sensor by sending a dummy byte (0x00)
        uint8_t squal = SPI.transfer(0x00); // Recieve the SQUAL byte from the PMW3389 sensor by sending a dummy byte (0x00)
        for (uint8_t i = 0; i < 5; i++) {
            SPI.transfer(0x00); // Send a dummy byte to read the rest of the motion burst data and discard it
        }
        result.isMotion = (motion & 0x80); // Check if the motion bit is set in the motion register
        result.dx = (int16_t)((uint16_t)deltaX_H << 8 | deltaX_L); // Combine the delta X high and low bytes into a signed 16-bit integer
        result.dy = (int16_t)((uint16_t)deltaY_H << 8 | deltaY_L); // Combine the delta Y high and low bytes into a signed 16-bit integer
        result.squal = squal; // Store the SQUAL value in the motion data struct
        digitalWrite(_ncsPin, HIGH); // Set the chip select pin high to stop communication with the PMW3389 sensor
        SPI.endTransaction(); // End the SPI transaction
        delayMicroseconds(1); // Wait to allow the PMW3389 sensor to process the request
        return result; // Return the motion data as a PMW3389_Motion struct
    }

    void PMW3389::setDPI(uint16_t dpi) {
        dpi = constrain(dpi, 100, 16000); // Constrain the DPI value to be between 100 and 16000
        dpi = dpi - (dpi % 50); // Round the DPI value down to the nearest multiple of 50
        uint16_t raw = dpi / 50;
        writeRegister(0x0E, raw); // Write the raw DPI value to the CPI register of the PMW3389 sensor
        writeRegister(0x0F, raw >> 8); // Write the high byte of the raw DPI value to the CPI register of the PMW3389 sensor
    }

    uint16_t PMW3389::getDPI() {
        uint8_t low = readRegister(0x0E); // Read the CPI register value from the PMW3389 sensor
        uint8_t high = readRegister(0x0F); // Read the high byte of the CPI register value from the PMW3389 sensor
        uint16_t raw = (uint16_t)(high << 8) | low; // Combine the high and low bytes of the CPI register value into a single 16-bit integer
        return raw * 50; // Return the DPI value by multiplying the register value by 50
    }