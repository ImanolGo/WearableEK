/**
 * @file			device_utils.c
 * @author			Imanol Gomez
 * @date			23.06.2016
 *
 * @details
 */

/******************** include files ***********************/
#include "em_cmu.h"
#include "em_gpio.h"
#include "stc3105.h"
#include "stc3115.h"
#include "device_utils.h"
#include "gpiosManager.h"
#include "i2c.h"
#include "adp8866.h"


/******************** defines *****************************/

/******************** prototypes **************************/

/******************** struct data type ********************/

/******************** private variables********************/

/******************** private function ********************/

/******************** interrupt function ******************/

/******************** global function *********************/


void initFirmwareUtils()
{
	firmwareVersion = 0;

	/* Configure PCFs*/
	GPIO_PinModeSet(gpioPortB, 11, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortB, 13, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortB, 14, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortC, 14, gpioModeInput, 0);

	int arr[4]={0,0,0,0};
	arr[0] = GPIO_PinInGet(gpioPortB, 11);
	arr[1] = GPIO_PinInGet(gpioPortB, 13);
	arr[2] = GPIO_PinInGet(gpioPortB, 14);
	arr[3] = GPIO_PinInGet(gpioPortC, 14);

	for (int i = 0; i < 4; ++i )
	{
		firmwareVersion *= 2;
		firmwareVersion = firmwareVersion + arr[i];
	}
}

uint8_t getFirmwareVersion()
{
	return firmwareVersion;
}


bool stc_testConnection()
{
	if(firmwareVersion == REVISION_0){
		return stc3105_testConnection();
	}
	else if(firmwareVersion == REVISION_MOON){
		return stc3115_testConnection();
	}
	else{
		return stc3115_testConnection();
	}
}
bool stc_initialize()
{
	if(firmwareVersion == REVISION_0){
		return stc3105_initialize();
	}
	else if(firmwareVersion == REVISION_MOON){
		return stc3115_initialize();
	}
	else{
		return stc3115_initialize();
	}
}

float stc_readVoltage()
{
	if(firmwareVersion == REVISION_0){
		return stc3105_readVoltage();
	}
	else if(firmwareVersion == REVISION_MOON){
		return stc3115_readVoltage();
	}
	else{
		return stc3115_readVoltage();
	}
}

void enableBatteryCharger(bool en)
{
	if(en){
		GPIO_PinOutSet(gpioPortE, 12); // Set to 1
	}
	else{
		GPIO_PinOutClear(gpioPortE, 12); // Set to 0
	}
}

void showBatteryVoltage()
{
	float vlt = stc_readVoltage();

	if(vlt>BATTERY_HALF){
		adp8866_set_led_green(LED_ID);
	}
	else if(vlt>BATTERY_FOURTH){
		adp8866_set_led_yellow(LED_ID);
	}
	else{
		adp8866_set_led_red(LED_ID);
	}
}

void startDevice()
{
	resetModules();
	setupI2C();
	testI2C();
}


