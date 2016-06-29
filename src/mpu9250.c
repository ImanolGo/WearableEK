/*
 * mpu9250.c
 *
 *  Created on: 20.06.2016
 *      Author: Imanol Gomez
 */

#include "mpu9250.h"
#include "i2c.h"


/** Power on and prepare for general usage.
 * This will activate the device and take it out of sleep mode (which must be done
 * after start-up). This function also sets both the accelerometer and the gyroscope
 * to their most sensitive settings, namely +/- 2g and +/- 250 degrees/sec, and sets
 * the clock source to use the X Gyro for reference, which is slightly better than
 * the default internal clock source.
 */
bool mpu9250_initialize(void)
{
	bool processed = mpu9250_wakeOnMotionConfiguration();
//	setClockSource(0);
//	setFullScaleGyroRange(MPU9250_GYRO_FULL_SCALE_250DPS);
//	setFullScaleAccelRange(MPU9250_FULL_SCALE_8G);
//	setSleepEnabled(false);

	return processed;
}

bool mpu9250_testConnection(void)
{
	uint8_t id = mpu9250_getDeviceID();
	if(id == WHOAMI_RESET_VAL)
		return true;

    return false;
}



uint8_t mpu9250_getDeviceID(void)
{
	return readI2C_1Byte(MPU9250_DEFAULT_ADDRESS,MPU9250_WHO_AM_I);
}

void mpu9250_processInterrupt(void)
{

}

bool mpu9250_wakeOnMotionConfiguration(void)
{
	bool completed = true;
	//< AccelmodeMake Sure Accel is running:

	//In PWR_MGMT_1 (0x6B) make CYCLE = 0, SLEEP = 0 and STANDBY = 0
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_PWR_MGMT_1, 0b00000000);
	//Set DIS_XA, DIS_YA, DIS_ZA = 0 and DIS_XG, DIS_YG, DIS_ZG = 1
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_PWR_MGMT_2, 0b00000111);

	//Set AccelLPF setting to 184 Hz Bandwidth:
	//ACCEL_CONFIG 2 (0x1D) set ACCEL_FCHOICE_B = 1 and A_DLPFCFG[2:]=1(b001)
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_ACCEL_CONFIG2, 0b00000101);

	//Enable Motion Interrupt:
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_INT_ENABLE, 0x40);

	//Enable AccelHardware Intelligence:
	//In MOT_DETECT_CTRL (0x69), set ACCEL_INTEL_EN = 1 and ACCEL_INTEL_MODE = 1
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_MOT_DETECT_CTRL, 0b11000000);

	//Set Motion Threshold:
	//In WOM_THR (0x1F), set the WOM_Threshold[7:0] to 1~255 LSBs (0~1020mg)
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_WOM_THR, 0xFF);

	//Set Frequency of Wake-up:
	//In LP_ACCEL_ODR (0x1E), set Lposc_clksel[3:0] = 0.24Hz ~ 500Hz
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_LP_ACCEL_ODR, 0b00000011);

	//Enable Cycle Mode (AccelLow Power Mode):
	//In PWR_MGMT_1 (0x6B) make CYCLE =1
	completed = completed && writeI2C_1Byte(MPU9250_DEFAULT_ADDRESS, MPU9250_PWR_MGMT_1, 0b00000011);

	return completed;
}

void configMPU9250(uint8_t gfs, uint8_t afs) {


switch(gfs) {
    case MPU9250_GFS_250:
    	mpu9250_gres = 250.0/32768.0;
    	break;
    case MPU9250_GFS_500:
    	mpu9250_gres = 500.0/32768.0;
    	break;
    case MPU9250_GFS_1000:
    	mpu9250_gres = 1000.0/32768.0;
    	break;
    case MPU9250_GFS_2000:
    	mpu9250_gres = 2000.0/32768.0;
      	break;
  }
  switch(afs) {
    case MPU9250_AFS_2G:
    	mpu9250_ares = 2.0/32768.0;
    	break;
    case MPU9250_AFS_4G:
    	mpu9250_ares = 4.0/32768.0;
    	break;
    case MPU9250_AFS_8G:
    	mpu9250_ares = 8.0/32768.0;
    	break;
    case MPU9250_AFS_16G:
    	mpu9250_ares = 16.0/32768.0;
    	break;
  }


//  // sleep off
//  writeI2c(_mpu9250addr, MPU9250_PWR_MGMT_1, 0x00);
//  delay(100);
//  // auto select clock source
//  writeI2c(_mpu9250addr, MPU9250_PWR_MGMT_1, 0x01);
//  delay(200);
//  // DLPF_CFG
//  writeI2c(_mpu9250addr, MPU9250_CONFIG, 0x03);
//  // sample rate divider
//  writeI2c(_mpu9250addr, MPU9250_SMPLRT_DIV, 0x04);
//  // gyro full scale select
//  writeI2c(_mpu9250addr, MPU9250_GYRO_CONFIG, gfs << 3);
//  // accel full scale select
//  writeI2c(_mpu9250addr, MPU9250_ACCEL_CONFIG, afs << 3);
//  // A_DLPFCFG
//  writeI2c(_mpu9250addr, MPU9250_ACCEL_CONFIG_2, 0x03);
//  // BYPASS_EN
//  writeI2c(_mpu9250addr, MPU9250_INT_PIN_CFG, 0x02);
//  delay(100);
}


/**
 @brief Read accelerometer
 @param [out] ax X-accel(g)
 @param [out] ay Y-accel(g)
 @param [out] az Z-accel(g)
*/
void readAccelXYZ(float * ax, float * ay, float * az) {
//  uint8_t data[6];
//  int16_t axc, ayc, azc;
//  readI2c(_mpu9250addr, MPU9250_ACCEL_XOUT_H, 6, data);
//  axc = ((int16_t)data[0] << 8) | data[1];
//  ayc = ((int16_t)data[2] << 8) | data[3];
//  azc = ((int16_t)data[4] << 8) | data[5];
//  *ax = (float)axc * _ares;
//  *ay = (float)ayc * _ares;
//  *az = (float)azc * _ares;
}

/**
 @brief Read gyro
 @param [out] gx X-gyro(degrees/sec)
 @param [out] gy Y-gyro(degrees/sec)
 @param [out] gz Z-gyro(degrees/sec)
*/
void readGyroXYZ(float * gx, float * gy, float * gz) {
//  uint8_t data[6];
//  int16_t gxc, gyc, gzc;
//  readI2c(_mpu9250addr, MPU9250_GYRO_XOUT_H, 6, data);
//  gxc = ((int16_t)data[0] << 8) | data[1];
//  gyc = ((int16_t)data[2] << 8) | data[3];
//  gzc = ((int16_t)data[4] << 8) | data[5];
//  *gx = (float)gxc * _gres;
//  *gy = (float)gyc * _gres;
//  *gz = (float)gzc * _gres;
}


/**
 @brief Read temperature
 @param [out] temperature temperature(degrees C)
*/
void readTemperature(float * temperature) {
  uint8_t data[2];
  int16_t tmc;

  data[0] = readI2C_1Byte(MPU9250_DEFAULT_ADDRESS,MPU9250_TEMP_OUT_L);
  data[1] = readI2C_1Byte(MPU9250_DEFAULT_ADDRESS,MPU9250_TEMP_OUT_H);
  tmc = ((int16_t)data[1] << 8) | data[0];
  *temperature = ((float)tmc) / 333.87 + 21.0;
}

/**
 @brief Check data ready
 @retval true data is ready
 @retval false data is not ready
*/
bool checkDataReady() {
  uint8_t drdy = readI2C_1Byte(MPU9250_DEFAULT_ADDRESS,MPU9250_INT_STATUS);

  if ( drdy & 0x01 ) {
    return true;
  } else {
    return false;
  }
}

