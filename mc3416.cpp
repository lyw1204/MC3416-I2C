#include "mc3416.h"


MC3416::MC3416() : _i2cAddress(MC3416_ADDRESS)
{
}

//Public Functions-------------------------------------------
bool MC3416::isFlipped(){
  return m_status.flip;
}

bool MC3416::isTilted(){
  return m_status.tilt;
}

void MC3416::enable_tilt_flip(int threshold = DEFAULT_THRESH){
  setMotionControl( 1 << TF_ENABLE );
  setInterruptEnable( 1 << TILT_INT_EN | 1 << FLIP_INT_EN );
  setThreshold(THRESH_TF, threshold);
}


void MC3416::standby(){setOpState(OPS_STANDBY);}
void MC3416::wake(){setOpState(OPS_WAKE);}

void MC3416::readFlags(){
  readStatus();
  readIntStatus();
}

//Private Functions-------------------------------------------
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
//Setter Functions ---------------------------------------------------------------------------------
void MC3416::setOpState(mc3416_OpState state){
  uint8_t state_val = static_cast<uint8_t>(state);
  overWrite(_i2cAddress, MODE, 0x03, state_val & 0x03);
}

void MC3416::setInterruptEnable(uint8_t value){
  writeRegister(_i2cAddress, INTR_CTRL, value);
}

void MC3416::setMotionControl(uint8_t value){
  writeRegister(_i2cAddress, MOTION_CTRL, value);
}

void MC3416::setRange(mc3416_Range range){
  m_range = static_cast<uint8_t>(range);
  overWrite(_i2cAddress, RANGE,  0b01111111, (range<<RANGE_0) | RANGE_MASK);
}

void MC3416::setSamplingRate(mc3416_SamplingRate sr){
  m_sr = static_cast<uint8_t>(sr);
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

void MC3416::setThreshold(mc3416_ThreshType type, unsigned int threshold){
  uint8_t addr_lsb = 0;
  uint8_t addr_msb = 0;
  switch (type){
    case THRESH_TF:
      addr_lsb = TF_THRESH_LSB;
      addr_msb = TF_THRESH_MSB;
      break;
    case THRESH_ANYM:
      addr_lsb = AM_THRESH_LSB;
      addr_msb = AM_THRESH_MSB;
      break;
    case THRESH_SHAKE:
      addr_lsb = SHK_THRESH_LSB;
      addr_msb = SHK_THRESH_MSB;

      break;
    
    default:
      //Invalid ThreshType
      return;
  }

  if (threshold > MAX_THRESH){ threshold = MAX_THRESH; };

  uint8_t LSB = (uint8_t) threshold;
  uint8_t MSB = (uint8_t)(threshold >> 8) & THRESH_MSB_MASK;
  writeRegister(_i2cAddress, addr_lsb, LSB);
  writeRegister(_i2cAddress, addr_msb, MSB);
  return;
}

