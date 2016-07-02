
#ifndef __SI7021_H
#define __SI7021_H

#include <stdint.h>
#include <stdbool.h>

#define SI7021_I2C_ADDR 0x80

// I2C commands
#define SI7021_RH_READ             			0xE5
#define SI7021_RH_READ_TEMP_READ           	0xE3
#define SI7021_RH_READ_POST_RH_TEMP_READ   	0xE0
#define SI7021_RH_READ_RESET               	0xFE
#define SI7021_RH_READ_USER1_READ          	0xE7
#define SI7021_USER1_WRITE         			0xE6
#define SI7021_FIRMWARE_REV   				0x20

#define SI7021_MAX_TEMP  					60
#define SI7021_MIN_TEMP  					50



typedef struct si7021_env {
    int celsiusHundredths;
    int fahrenheitHundredths;
    unsigned int humidityBasisPoints;
} si7021_env;

// same as above but without fahrenheit parameter and RH %
typedef struct si7021_thc {
    int celsiusHundredths;
    unsigned int humidityPercent;
} si7021_thc;


void si7201_initialize(void);
bool si7201_testConnection(void);
uint8_t si7021_getFirmwareRevision(void);

int si7021_getCelsiusHundredths();
float si7021_getTempCelsius();

void si7021_checkTemperature();

bool si7021_coolingDown;


#endif
