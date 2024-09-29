#include <Arduino.h>
#include "I2C.h"

#define TSL2591_ADRESS 0x29

#define TSL2591_REGISTER_ENABLE 0x00
#define TSL2591_REGISTER_CONTROL 0x01
#define TSL2591_REGISTER_ID 0x12
#define TSL2591_REGISTER_CHAN0_LOW 0x14      
#define TSL2591_REGISTER_CHAN0_HIGH 0x15     
#define TSL2591_REGISTER_CHAN1_LOW 0x16    
#define TSL2591_REGISTER_CHAN1_HIGH 0x17

#define TSL2591_DISABLE 0x00
#define TSL2591_ENABLE 0x03
#define TSL2591_GAIN_MED 0x10
#define TSL2591_INTEGRATIONTIME_300MS 0x02

#define TSL2591_COMMAND_BIT 0xA0

#define TSL2591_LUX_DF (408.0F)   ///< Lux cooefficient
#define TSL2591_LUX_COEFB (1.64F) ///< CH0 coefficient
#define TSL2591_LUX_COEFC (0.59F) ///< CH1 coefficient A
#define TSL2591_LUX_COEFD (0.86F) ///< CH2 coefficient B

void TSLenable();
void TSLdisable();
void TSLconfig();
uint8_t TSLreadID();
float TSLreadLux();
