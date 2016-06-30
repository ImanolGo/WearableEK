/*
 * s100_switch.c
 *
 *  Created on: 21.06.2016
 *      Author: Imanol Gomez
 */

#include "em_gpio.h"
#include "em_cmu.h"
#include "gpiointerrupt.h"
#include "adp8866.h"
#include "time_utils.h"
#include "stc3105.h"
#include "stc3115.h"
#include "mpu9250.h"
#include "device_utils.h"
#include "noise.h"
#include "gpiosManager.h"

void gpioCallback(uint8_t pin)
{
	if (pin == SWITCH_PIN)
	{
	int input = GPIO_PinInGet(gpioPortC, SWITCH_PIN);

	if(input==0){
		switchPressed = true;
		switchTicks = msTicks;
	}
	else
	{
		switchPressed = false;
		switchTogglePower();

		if((msTicks - switchTicks)> SWITCH_RESTART_DELAY)
		{
			startDevice();
			//showBatteryVoltage();
		}

	}

	}

	else if(pin==BATTERY_CHG_PIN)
	{
		int input = GPIO_PinInGet(gpioPortE, BATTERY_CHG_PIN);
		if(input==0){
			startDevice();
		}
		else
		{
			//stopTimer();
		}
	}

	else if(pin==ADP_INT_PIN)
	{
		int input = GPIO_PinInGet(gpioPortD, ADP_INT_PIN);
		if(input==0){
			adp8866_processInterrupt();
		}
		else
		{
			//stopTimer();
		}
	}

	else if(pin==MPU_INT_PIN)
	{
		int input = GPIO_PinInGet(gpioPortD, MPU_INT_PIN);
		if(input==0){
			mpu9250_processInterrupt();
		}
		else
		{
			//stopTimer();
		}
	}
}

void updateColor()
{
	if(!s100On){
		return;
	}

	currentColor.h = (currentColor.h + 1.0);
	if(currentColor.h>=360.0){
		currentColor.h = 0;
	}

	//currentColor.v = getNoise128(noiseTimer);

	RGB colorRGB = hsv2rgb(currentColor);
	adp8866_set_led_rgb(LED_ID, &colorRGB);
	noiseTimer = noiseTimer + 0.3;

}
void initGpios()
{
	/* Init variables */
	s100On = false;
	currentColor.h = 0; currentColor.s = 0; currentColor.v = 127;

	/* Enable GPIO in CMU */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Initialize GPIO interrupt dispatcher */
	GPIOINT_Init();

	/* Configure PC15*/
	GPIO_PinModeSet(gpioPortC, SWITCH_PIN, gpioModeInput, 0); //Switch

	GPIO_PinModeSet(gpioPortE, BATTERY_CHG_PIN, gpioModeInput, 1);  //BQ51050B CHG
	GPIO_PinModeSet(gpioPortE, BQ51050B_CTRL_PIN, gpioModeWiredAnd, 1);  //BQ51050B CTRL open drain output

	GPIO_PinModeSet(gpioPortD, ADP_INT_PIN, gpioModeInput, 1);  //ADP8866 nINT - Active Low
	GPIO_PinModeSet(gpioPortD, MPU_INT_PIN, gpioModeInput, 1);  //MPU9250 nINT - Active Low

	GPIO_PinModeSet(gpioPortD, ADP8866_NRST_PIN, gpioModePushPull , 0); // ADP8866 nRST
	GPIO_PinModeSet(gpioPortE, BLE_RST_PIN, gpioModePushPull , 0); // BLE RESETn

	//Delay(100);
	//GPIO_PinOutSet(gpioPortD, 7); // Set to 1


	/* Register callbacks before setting up and enabling pin interrupt. */
	GPIOINT_CallbackRegister(SWITCH_PIN, gpioCallback);
	GPIOINT_CallbackRegister(BATTERY_CHG_PIN, gpioCallback);
	GPIOINT_CallbackRegister(ADP_INT_PIN, gpioCallback);
	GPIOINT_CallbackRegister(MPU_INT_PIN, gpioCallback);

	/* Set rising and falling edge interrupt for the port */
	GPIO_IntConfig(gpioPortC, SWITCH_PIN, true, true, true);
	GPIO_IntConfig(gpioPortE, BATTERY_CHG_PIN, true, true, true);
	GPIO_IntConfig(gpioPortD, ADP_INT_PIN, true, true, true);
	GPIO_IntConfig(gpioPortD, MPU_INT_PIN, true, true, true);

	switchElapsedTime = 1000; //elapsed time in ms
	switchTicks = msTicks;
	switchOnOffDelay = 50;
	switchPressed = false;
	noiseTimer = 0.0;
}

/**************************************************************************//**
 * @brief resets the modules
 *****************************************************************************/
void resetModules()
{
	GPIO_PinOutClear(gpioPortD, ADP8866_NRST_PIN); // Set to 0
	GPIO_PinOutClear(gpioPortE, BLE_RST_PIN); // Set to 0
	Delay(200);
	GPIO_PinOutSet(gpioPortD, ADP8866_NRST_PIN); // Set to 1
	GPIO_PinOutSet(gpioPortE, BLE_RST_PIN); // Set to 1
	Delay(200);
}



void switchTogglePower()
{
	if(s100On)
	{
		//currentColor.h = 0; currentColor.s = 0;  currentColor.v = 0;
		adp8866_set_all_black();
		s100On = false;
	}

	else
	{
		RGB colorRGB = hsv2rgb(currentColor);
		//adp8866_set_led_rgb_pulse(ledID,colorRGB);
		adp8866_set_led_rgb(LED_ID,&colorRGB);
		s100On = true;
	}
}






