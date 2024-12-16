#include "myi2c.h"

Myi2c_interface::Myi2c_interface()
{

}

uint8_t Myi2c_interface::overWrite(uint8_t addr, uint8_t reg, uint8_t mask, uint8_t new_val){
  uint8_t buf_val = readRegister(addr, reg);
  buf_val &= ~mask; //Clear the masked bits
  buf_val |= new_val;
  return writeRegister(reg, buf_val);
}

uint8_t Myi2c_interface::readRegister(uint8_t addr, uint8_t reg){
  TinyWireM.beginTransmission(addr);
  TinyWireM.write(reg);
  TinyWireM.endTransmission(false);
  TinyWireM.requestFrom(addr, (uint8_t) 1);

  return TinyWireM.read();
}

uint8_t Myi2c_interface::readBytes(uint8_t addr, uint8_t reg, uint8_t num_bytes, uint8_t *destination){
  TinyWireM.beginTransmission(addr);
  TinyWireM.write(reg);
  uint8_t status = TinyWireM.endTransmission(false);
  TinyWireM.requestFrom(addr, num_bytes);

  while(uint8_t i = 0; i< num_bytes; i++){
    if (TinyWireM.available()){
         destination[i] = TinyWireM.read();
    }
  }
  return status;
}

uint8_t Myi2c_interface::writeRegister(uint8_t addr, uint8_t reg, uint8_t val){
  TinyWireM.beginTransmission(addr);
  TinyWireM.write(reg);
  TinyWireM.write(val);
  return TinyWireM.endTransmission();
}