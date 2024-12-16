#ifndef MC3416
#define MC3416

#define __AVR_ATtiny24__

#include "Arduino.h"


#include "mc3416_regmap.h"
#include "myi2c.h"

#define MC3416_ADDRESS (0x4C)


//ALT Address with VPP HIGH
//#define MC3416_ADDRESS 0x6C

#ifndef AXESSTRUCTURE
#define AXESSTRUCTURE
struct sIntAxes
{
	int16_t X = 0;
	int16_t Y = 0;
	int16_t Z = 0;
};
#endif /* AXESSTRUCTURE */

#ifndef STATUSSTRUCTURE
#define STATUSSTRUCTURE
struct sStatusFlags
{
    bool = false;
    bool flip = false;
    bool anym = false;
    bool shake = false;
    bool tilt_35 = false;
    bool acq = false;
};
#endif

class MC3416 : public Myi2c_interface
{
    public:
        MC3416();

    private:
        mc3416_Range m_range;
        mc3416_SamplingRate m_sr;
        sIntAxes m_rawOut;
        sStatusFlags m_status;
        sStatusFlags m_int_status;
        
        uint8_t readStatus();
        void setRange(mc3416_Range range);
        void setSamplingRate(mc3415_SamplingRate sr);
        void setOffset(mc3416_axes axis, short offset);
        uint8_t readStatus();
        uint8_t readIntStatus();
        void readRaw();

}

#endif