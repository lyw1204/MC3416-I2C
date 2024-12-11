#include "mc3416.h"


MC3416::MC3416(USI_TWI *w){
    _wire = w;    

    i2cAddress = MC3416_ADDRESS;
}

bool MC3416::INIT(){

}

void MC3416::STANDBY(){
}


void MC3416::setRange(mc3416_Range range){
  this->m_range = range;
  overWrite(RANGE,  0b01111111, (range<<RANGE_0) | RANGE_MASK);
}

void MC3416::setSamplingRate(mc3415_SamplingRate sr){
  this->m_sr = sr;
  this->overWrite(SR, 0b00000111, sr);
}



void MC3416::readRaw(){
  this->m_rawOut.X = (this->readRegister(XOUT_EX_H) << 8 ) | this->readRegister(XOUT_EX_L);
  this->m_rawOut.Y = (this->readRegister(YOUT_EX_H) << 8 ) | this->readRegister(YOUT_EX_L);
  this->m_rawOut.Z = (this->readRegister(ZOUT_EX_H) << 8 ) | this->readRegister(ZOUT_EX_L);
}



void MC3416::overWrite(uint8_t reg, uint8_t mask, uint8_t new_val){
  uint8_t buf_val = readRegister(reg);
  buf_val &= ~mask; //Clear the masked bits
  buf_val |= new_val;
  writeRegister(reg, buf_val);
}

uint8_t MC3416::readRegister(uint8_t reg){
  _wire->beginTransmission(i2cAddress);
  _wire->write(reg);
  uint8_t buffer = 0;
  while (_wire->Available()){
    buffer = _wire.read();
  }
  return buffer;


}
uint8_t MC3416::writeRegister(uint8_t reg, uint8_t val){
  _wire->beginTransmission(i2cAddress);
  _wire->write(reg);
  _wire->write(val);
  return _wire->endTransmission();
}