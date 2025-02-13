#include "myi2c.h"

Myi2c_interface::Myi2c_interface()
{
  Wire.begin();
}

uint8_t Myi2c_interface::overWrite(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t new_val){
  uint8_t buf_val = readRegister(addr, reg);
  buf_val &= ~mask; //Clear the masked bits
  buf_val |= (new_val & mask); //Set the masked bits to new_val
  return writeRegister(addr, reg, buf_val);
}

uint8_t Myi2c_interface::readRegister(uint8_t addr, uint8_t reg){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, (uint8_t) 1);

  return Wire.read();
}

uint8_t Myi2c_interface::readBytes(uint8_t addr, uint8_t reg, uint8_t num_bytes, uint8_t *destination){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  uint8_t status = Wire.endTransmission(false);
  Wire.requestFrom(addr, num_bytes);

  for(uint8_t i = 0; i< num_bytes; i++){
    if (Wire.available()){
         destination[i] = Wire.read();
    }
  }
  return status;
}

uint8_t Myi2c_interface::writeRegister(uint8_t addr, uint8_t reg, uint8_t val){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  return Wire.endTransmission();
}