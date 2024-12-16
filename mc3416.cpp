#include "mc3416.h"


MC3416::MC3416() : _i2cAddress(MC3416_ADDRESS)
{
}

void MC3416::setRange(mc3416_Range range){
  m_range = range;
  overWrite(_i2cAddress, RANGE,  0b01111111, (range<<RANGE_0) | RANGE_MASK);
}

void MC3416::setSamplingRate(mc3415_SamplingRate sr){
  m_sr = sr;
  overWrite(_i2cAddress, SR, 0b00000111, sr);
}

void MC3416::setOffset(mc3416_axes axis, short offset){
  uint8_t REG_L = 0;
  uint8_t REG_H = 0;

  switch (axis){
    case x:
      REG_L = XOFFL;
      REG_H = XOFFH;
      break;
    case y:
      REG_L = YOFFL;
      REG_H = YOFFH;
      break;
    case z:
      REG_L = ZOFFL;
      REG_H = ZOFFH;
      break;
    default:
      return;
  }
  
  if (offset >= MAX_OFFSET){ offset = MAX_OFFSET; }
  else if (offset < MIN_OFFSET){ offset = -MIN_OFFSET; }
  uint8_t lsb = (uint8_t) offset;
  uint8_t msb = OFFSET_MSB_MASK & ((uint8_t)(offset >> 8));
  writeRegister(_i2cAddress, REG_L, lsb);
  overWrite(_i2cAddress, REG_H, OFFSET_MSB_MASK, msb);

}

uint8_t MC3416::readStatus(){
  uint8_t buf = readRegister(_i2cAddress, STATUS_2);
  m_status.tilt = 0x01 & (buf >> TILT_FLAG);
  m_status.flip = 0x01 & (buf >> FLIP_FLAG);
  m_status.anym = 0x01 & (buf >> ANYM_FLAG);
  m_status.shake = 0x01 & (buf >> SHAKE_FLAG);
  m_status.tilt_35 = 0x01 & (buf >> TILT_35_FLAG);
  m_status.acq = 0x01 & (buf >> NEW_DATA);

  return buf;
}

uint8_t MC3416::readIntStatus(){
  uint8_t buf = readRegister(_i2cAddress, INTR_STAT_2);
  m_int_status.tilt = 0x01 & (buf >> TILT_INT);
  m_int_status.flip = 0x01 & (buf >> FLIP_INT);
  m_int_status.anym = 0x01 & (buf >> ANYM_INT);
  m_int_status.shake = 0x01 & (buf >> SHAKE_INT);
  m_int_status.tilt_35 = 0x01 & (buf >> TILT_35_INT);
  m_int_status.acq = 0x01 & (buf >> ACQ_INT);

  return buf;
}

void MC3416::readRaw(){
  m_rawOut.X = (readRegister(_i2cAddress, XOUT_EX_H) << 8 ) | readRegister(_i2cAddress, XOUT_EX_L);
  m_rawOut.Y = (readRegister(_i2cAddress, YOUT_EX_H) << 8 ) | readRegister(_i2cAddress, YOUT_EX_L);
  m_rawOut.Z = (readRegister(_i2cAddress, ZOUT_EX_H) << 8 ) | readRegister(_i2cAddress, ZOUT_EX_L);
}