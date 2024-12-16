//Register Table

#define DEV_STAT (0x05)

#define INTR_CTRL (0x06)
#define TILT_INT_EN (0U)
#define FLIP_INT_EN (1U)
#define ANYM_INT_EN (2U)
#define SHAKE_INT_EN (3U)
#define TILT_35_INT_EN (4U)
#define AUTO_CLR_EN (6U)
#define ACQ_INT_EN (7U)

#define MODE (0x07) //Mode

#define STATE_0 (0U)
#define STATE_1 (1U)
#define I2C_WDT_NEG (4U)
#define I2C_WDT_POS (5U)
#define IPP (6U)
#define IAH (7U)

//Sampling Rate
#define SR (0x08)
#define RATE_0 (0U)
#define RATE_1 (1U)
#define RATE_2 (2U)

//Motion Control Flags and Interrupts
#define MOTION_CTRL (0x09)
#define TF_ENABLE (0U)
#define MOTION_LATCH (1U)
#define ANYM_EN (2U)
#define SHAKE_EN (3U)
#define TILT_35_EN (4U)
#define Z_AXIS_ORT (5U) // 0: +Z on top of PKG
#define RAW_PROC_STAT (6U)
#define MOTION_RESET (7U)

//Output Data Registers
#define XOUT_EX_L (0x0D)
#define XOUT_EX_H (0x0E)
#define YOUT_EX_L (0x0F)
#define YOUT_EX_H (0x10)
#define ZOUT_EX_L (0x11)
#define ZOUT_EX_H (0x12)

//Status Registers
#define STATUS_2 (0x13)
#define TILT_FLAG (0U)
#define FLIP_FLAG (1U)
#define ANYM_FLAG (2U)
#define SHAKE_FLAG (3U)
#define TILT_35_FLAG (4U)
#define NEW_DATA (7U)

//Interrupt Status Register
#define INTR_STAT_2 (0x14)
#define TILT_INT (0U)
#define FLIP_INT (1U)
#define ANYM_INT (2U)
#define SHAKE_INT (3U)
#define TILT_35_INT (4U)
#define ACQ_INT (7U)

//Range and Scale Control Register
#define RANGE (0x20)
#define RANGE_0 (4U)
#define RANGE_1 (5U)
#define RANGE_2 (6U)
#define RANGE_MASK (0b00001001)


//X Offset
#define XOFFL (0x21)
#define XOFFH (0x22)
#define XGAIN_8 (7U)

//Y Offset
#define YOFFL (0x23)
#define YOFFH (0x24)
#define YGAIN_8 (7U)

//Z Offset
#define ZOFFL (0x25)
#define ZOFFH (0x26)
#define ZGAIN_8 (7U)
#define MAX_OFFSET 8191
#define MIN_OFFSET -8192
#define OFFSET_MSB_MASK 0b01111111

//Gains
#define XGAIN (0x27)
#define YGAIN (0x28)
#define ZGAIN (0x29)

//Tilt & Flip Threshold 
#define TF_THRESH_LSB (0x40)
#define TF_THRESH_MSB (0x41)
#define TF_DB (0x42)

//AnyMotion Threshold
#define AM_THRESH_LSB (0x43)
#define AM_THRESH_MSB (0x44)
#define AM_DB (0x45)

//Shake Threshold
#define SHK_THRESH_LSB (0x46)
#define SHK_THRESH_MSB (0x47)

//Shake Duration - Pk-Pk
#define PK_P2P_DUR_THRESH_LSB (0x48)
#define PK_P2P_DUR_THRESH_MSB (0x49)

//Timer Control Registers
#define TIMER_CTRL (0x4A)
#define TILT_35_0 (0U)
#define TILT_35_1 (1U)
#define TEMP_PERIOD_0 (4U)
#define TEMP_PERIOD_1 (5U)
#define TEMP_PERIOD_2 (6U)
#define TEMP_PER_INT_EN (7U)


//Enums

enum mc3416_Range
{
	AFS_2G = 0,
	AFS_4G,
	AFS_8G,
	AFS_16G,
    AFS_12G
};

enum mc3416_SamplingRate
{
    SR_128 = 0,
    SR_256,
    SR_512,
    SR_RES1,
    SR_RES2,
    SR_1024,
    SR_RES3,
    SR_RES4
};

enum mc3416_axes
{
    x = 0,
    y,
    z
};

