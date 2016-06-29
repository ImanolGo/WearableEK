
#ifndef __STC3105_H
#define __STC3105_H

#include <stdint.h>
#include <stdbool.h>


#define STC3105_DEFAULT_ADDRESS 	0xE0

#define STC3105_REG_MODE 			0x00 // R/W Mode register
#define STC3105_REG_CTRL			0x01 // R/W Control and status register

#define STC3105_REG_CHARGE_LOW		0x02 // R State-of-charge data, bits 0-7
#define STC3105_REG_CHARGE_HIGH		0x03 // R State-of-charge data, bits 8-15
#define STC3105_REG_COUNTER_LOW		0x04 // R Number of conversions, bits 0-7
#define STC3105_REG_COUNTER_HIGH	0x05 // R Number of conversions, bits 8-15
#define STC3105_REG_CURRENT_LOW		0x06 // R Battery current value, bits 0-7
#define STC3105_REG_CURRENT_HIGH    0x07 // R Battery current value, bits 8-15
#define STC3105_REG_VOLTAGE_LOW 	0x08 // R Battery voltage value, bits 0-7
#define STC3105_REG_VOLTAGE_HIGH	0x09 // R Battery voltage value, bits 8-15
#define STC3105_REG_SOC_BASE_LOW	0x10 // R/W SOC base value, bits 0-7
#define STC3105_REG_SOC_BASE_HIGH	0x11 // R/W SOC base value, bits 8-15
#define STC3105_REG_ALARM_SOC_LOW	0x12 // R/W SOC alarm level, bits 0-7
#define STC3105_REG_ALARM_SOC_HIGH	0x13 // R/W SOC alarm level, bits 8-15
#define STC3105_REG_ALARM_VOLTAGE	0x14 // R/W Battery low voltage alarm level
#define STC3105_REG_CURRENT_THRES	0x15 // R/W Current threshold for the voltage relaxation counter
#define STC3105_REG_RELAX_COUNT		0x16 // R Voltage relaxation counter

#define STC3105_REG_ID				0x18 // R Part type ID = 12h
#define STC3105_DEFAULT_ID			0x12 // Default ID 12h

#define STC3105_REG_RAM0 			0x20 // R/W Working register 0 for gas gauge
// ...
// ...
#define STC3105_REG_RAM15			0x2F // R/W Working register 15 for gas gauge


bool stc3105_initialize(void);
bool stc3105_testConnection(void);
bool stc3105_enableOperatingMode(bool enable);
uint8_t stc3105_registerID(void);

float stc3105_readVoltage(void);
float stc3105_readCurrent(void);


float stc3105_voltage; // V
float stc3105_current; // A

#endif
