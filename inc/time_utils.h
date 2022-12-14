/*
 * time_utils.h
 *
 *  Created on: 20.06.2016
 *      Author: Imanol Gomez
 */

#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

#include <stdint.h>

#define TEMP_SENSOR_REFRESHTIME 900

/**************************************************************************//**
 * @brief TIMER0_IRQHandler
 * Interrupt Service Routine TIMER0 Interrupt Line
 *****************************************************************************/
void TIMER0_IRQHandler(void);


void Delay3(uint32_t delay);

void Delay2( uint32_t msec );

volatile uint32_t msTicks; /* counts 1ms timeTicks */

void Delay(uint32_t dlyTicks);

void initTime();

void startTimer();

void stopTimer();

float elapsedTimeTempSensor;

#endif /* TIME_UTILS_H_ */
