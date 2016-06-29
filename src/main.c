/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"

//#include "InitDevice.h"
#include "i2c.h"
#include "noise.h"
#include "stc3105.h"
#include "stc3115.h"
#include "si7021.h"
#include "mpu9250.h"
#include "adp8866.h"
#include "device_utils.h"
#include "time_utils.h"
#include "gpiosManager.h"





/**************************************************************************//**
 * @brief Sets all necessary parameters
 *****************************************************************************/
void initializeSystem()
{
	/* Chip errata */
	CHIP_Init();
	// enter_DefaultMode_from_RESET();

	/* Enabling clock to the I2C, GPIO, LE */
	CMU_ClockEnable(cmuClock_I2C0, true);
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Initialize firmware parameters */
	initFirmwareUtils();

	/* Initialize time parameters */
	initTime();

	/* Initialize noise parameters */
	initializeNoise();


	/* Initialize gpios */
	initGpios();


	//CMU_ClockEnable(cmuClock_CORELE, true);

	// Enabling USART0 (see errata)
	// CMU_ClockEnable(cmuClock_USART0, true);

	/* Starting LFXO and waiting until it is stable */
	//CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

	/* Routing the LFXO clock to the RTC */
	//CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);
	//CMU_ClockEnable(cmuClock_RTC, true);
}



/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
	initializeSystem();
	startDevice();

	/* Infinite loop */
	while (1) {
		//We Sleep even if we wake up from the interrupt
		EMU_EnterEM1();
		//EMU_EnterEM2(false); //Go to EM2
		//updateColor();
	}
}
