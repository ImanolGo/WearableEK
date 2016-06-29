/*
 * gpiosManager.h
 *
 *  Created on: 21.06.2016
 *      Author: Imanol Gomez
 */

#ifndef GPIOS_MANAGER_H_
#define GPIOS_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>

#include "adp8866.h"

#define SWITCH_PIN 15
#define BATTERY_CHG_PIN 11
#define ADP_INT_PIN 6
#define MPU_INT_PIN 4
#define BQ51050B_TS_CTRL_PIN 12
#define ADP8866_NRST_PIN 7
#define BLE_RST_PIN 13



/**************************************************************************//**
 * @brief  Gpio callback
 * @param  pin - pin which triggered interrupt
 *****************************************************************************/
void gpioCallback(uint8_t pin);

/**************************************************************************//**
 * @brief  init Gpios
 *****************************************************************************/
void initGpios();

void switchTogglePower();

void updateColor();

void resetModules();



uint32_t 	switchElapsedTime;//elapsed time in ms
uint32_t 	switchTicks;//number of switch ticks
uint32_t 	switchOnOffDelay;
uint32_t 	switchBatteryDelay;
double 		noiseTimer;

HSV		 	currentColor;
bool 	 	switchPressed;
bool		s100On;


#endif /* S100_SWITCH_H_ */
