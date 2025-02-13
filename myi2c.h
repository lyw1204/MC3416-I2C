#ifndef MYI2C_H
#define MYI2C_H


#include <Wire.h>  // Include the Wire library for I2C communication

class Myi2c_interface {
public:
    // Constructor
    Myi2c_interface();

    // Method to overwrite specific bits in a register
    uint8_t overWrite(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t new_val);

    // Method to read a single byte from a register
    uint8_t readRegister(uint8_t addr, uint8_t reg);

    // Method to read multiple bytes from a register into a buffer
    uint8_t readBytes(uint8_t addr, uint8_t reg, uint8_t num_bytes, uint8_t *destination);

    // Method to write a single byte to a register
    uint8_t writeRegister(uint8_t addr, uint8_t reg, uint8_t val);
};

#endif
