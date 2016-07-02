/**
 * @file			time_utils.c
 * @author			Imanol Gomez
 * @date			23.06.2016
 *
 * @details
 */

/******************** include files ***********************/
#include "em_cmu.h"
#include "em_timer.h"
#include "si7021.h"
#include "gpiosManager.h"
#include "device_utils.h"
#include "rtcdrv.h"
#include "em_rtc.h"
#include "time_utils.h"


/******************** defines *****************************/

/* 13671 Hz -> 14Mhz (clock frequency) / 1024 (prescaler)
  Setting TOP to 27342 results in an overflow each 2 seconds
   */
//#define TOP 27342
//#define TOP 1367
#define TOP 684




/******************** prototypes **************************/

/******************** struct data type ********************/

/******************** private variables********************/

/******************** private function ********************/

/******************** interrupt function ******************/

/******************** global function *********************/


/**************************************************************************//**
 * @brief  Delay function, does not depend on interrupts.
 *****************************************************************************/
void Delay2( uint32_t msec )
{
/* RTC frequency is LFXO divided by 32 (prescaler) */
#define RTC_FREQ (32768 / 32)

  RTC_IntDisable( RTC_IF_COMP0 );
  RTC_IntClear( RTC_IF_COMP0 );
  RTC_CompareSet( 0, (RTC_FREQ * msec ) / 1000 ); /* Calculate trigger value */

  RTC_Enable( true );
  while ( !( RTC_IntGet() & RTC_IF_COMP0 ) );     /* Wait for trigger */
  RTC_Enable( false );
}

void Delay3(uint32_t delay) {
	delay*=2000;
	while (delay--);
}


/**************************************************************************//**
 * @brief initTime
 * Setup SysTick Timer for 1 msec interrupts
 *****************************************************************************/
void initTime(void)
{
	if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

	 /* Enable clock for TIMER0 module */
	  CMU_ClockEnable(cmuClock_TIMER0, true);

	  /* Select TIMER0 parameters */
	  TIMER_Init_TypeDef timerInit =
	  {
	    .enable     = true,
	    .debugRun   = true,
	    .prescale   = timerPrescale1024,
	    .clkSel     = timerClkSelHFPerClk,
	    .fallAction = timerInputActionNone,
	    .riseAction = timerInputActionNone,
	    .mode       = timerModeUp,
	    .dmaClrAct  = false,
	    .quadModeX4 = false,
	    .oneShot    = false,
	    .sync       = false,
	  };

	  startTimer();

	  /* Set TIMER Top value */
	  TIMER_TopSet(TIMER0, TOP);

	  /* Configure TIMER */
	  TIMER_Init(TIMER0, &timerInit);

	  elapsedTimeTempSensor = 0.0;
}

void TIMER0_IRQHandler(void)
{

	/* Clear flag for TIMER0 overflow interrupt */
	TIMER_IntClear(TIMER0, TIMER_IF_OF);

	if(elapsedTimeTempSensor >= TEMP_SENSOR_REFRESHTIME)
	{
		si7021_checkTemperature();
		elapsedTimeTempSensor = 0.0;
	}
	elapsedTimeTempSensor+= (float)TOP/13671.0;

	updateColor();

}


/**************************************************************************//**
 * @brief SysTick_Handler
 * Interrupt Service Routine for system tick counter
 *****************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

/**************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 *****************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}


/**************************************************************************//**
 * @brief SysTick_Disable
 * Disable systick interrupts
 *****************************************************************************/
void SysTick_Disable(void)
{
  SysTick->CTRL = 0x0000000;
}


void startTimer()
{
	/* Enable overflow interrupt */
	TIMER_IntEnable(TIMER0, TIMER_IF_OF);

	/* Enable TIMER0 interrupt vector in NVIC */
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void stopTimer()
{
	/* Disable overflow interrupt */
	TIMER_IntDisable(TIMER0, TIMER_IF_OF);

	/* Disable TIMER0 interrupt vector in NVIC */
	NVIC_DisableIRQ(TIMER0_IRQn);
}

