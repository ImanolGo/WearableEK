/*
 * device_utils.h
 *
 *  Created on: 23.06.2016
 *      Author: Imanol Gomez
 */

#ifndef DEVICE_UTILS_H_
#define DEVICE_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

#define LED_ID 2

#define REVISION_0 15
#define REVISION_MOON 1

#define BATTERY_FULL 4.2f
#define BATTERY_HALF 3.75f
#define BATTERY_FOURTH 3.7f
#define BATTERY_EIGHTH 3.65f


void initFirmwareUtils();
uint8_t getFirmwareVersion();
uint8_t firmwareVersion;

void enableBatteryCharger(bool en);
void showBatteryVoltage();

void startDevice(void);

bool stc_testConnection();
bool stc_initialize();
float stc_readVoltage();



#endif /* FIRMWARE_UTILS_H_ */
