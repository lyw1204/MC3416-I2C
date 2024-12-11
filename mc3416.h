#ifndef MC3416
#define MC3416

#define __AVR_ATtiny24__

#include "mc3416_regmap.h"
#include "Arduino.h"

#include <TinyWireM.h>

#define MC3416_ADDRESS (0x4C)


//ALT Address with VPP HIGH
//#define MC3416_ADDRESS 0x6C

#ifndef AXESSTRUCTURE
#define AXESSTRUCTURE
struct sIntAxes
{
	int16_t X;
	int16_t Y;
	int16_t Z;
};
#endif /* AXESSTRUCTURE */



class MC3416
{
    public:
        MC3416(USI_TWI *w);

    private:
        USI_TWI *_wire;
        mc3416_Range m_range;
        mc3415_SamplingRate m_sr;
        sIntAxes m_rawOut;

        uint8_t writeRegister(uint8_t reg, uint8_t val);


}

#endif