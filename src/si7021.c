/**
 * @file			si7021.c
 * @author			Imanol Gomez
 * @date			13.06.2016
 *
 * @details
 */

/******************** include files ***********************/
#include "si7021.h"
#include "device_utils.h"
#include "i2c.h"



/******************** defines *****************************/

// compound commands
uint8_t SI7021_FIRMWARE_WRITE[]  = { 0x84, 0xB8 };
//uint8_t SI7021_SERIAL1_READ[]   = { 0xFA, 0x0F };
//uint8_t SI7021_SERIAL2_READ[]   = { 0xFC, 0xC9 };


/******************** prototypes **************************/

/******************** struct data type ********************/

/******************** private variables********************/

/******************** private function ********************/

/******************** interrupt function ******************/

/******************** global function *********************/


void si7021_initialize(void)
{
	si7021_coolingDown = false;
}

bool si7201_testConnection(void)
{
	uint8_t id = si7021_getFirmwareRevision();
	if(id == SI7021_FIRMWARE_REV)
		return true;

    return false;
}


uint8_t si7021_getFirmwareRevision(void)
{
	I2C_Read_Def i2c_readTransfer;
	uint8_t i2c_read_data[1] = {-1};
	uint8_t i2c_write_data[1] = { SI7021_FIRMWARE_WRITE[1]};

	i2c_readTransfer.addr  = SI7021_I2C_ADDR;
	i2c_readTransfer.regstr  = SI7021_FIRMWARE_WRITE[0];
	i2c_readTransfer.write_data  = i2c_write_data;
	i2c_readTransfer.write_len  = 1;

	i2c_readTransfer.read_data = i2c_read_data;
	i2c_readTransfer.read_len  = 1;

	readI2C(&i2c_readTransfer);

	return i2c_readTransfer.read_data[0];

}

int si7021_getCelsiusHundredths() {

	I2C_Read_Def i2c_readTransfer;
	uint8_t i2c_read_data[2] = {-1,-1};

	i2c_readTransfer.addr  = SI7021_I2C_ADDR;
	i2c_readTransfer.regstr  = SI7021_RH_READ_TEMP_READ;
	i2c_readTransfer.write_len  = 0;

	i2c_readTransfer.read_data = i2c_read_data;
	i2c_readTransfer.read_len  = 2;

	readI2C(&i2c_readTransfer);

    long tempraw = (long)i2c_readTransfer.read_data[0] << 8 | i2c_readTransfer.read_data[1];
    int temp = ((17572 * tempraw) >> 16) - 4685;
    return temp;
}

float si7021_getTempCelsius()
{
	float temp = (float)si7021_getCelsiusHundredths()/100.0;
    return temp;
}

void si7021_checkTemperature()
{
	if(si7021_coolingDown && si7021_getTempCelsius()< SI7021_MIN_TEMP ){
		si7021_coolingDown = false;
		enableBatteryCharger(true);

	}
	else if(!si7021_coolingDown && si7021_getTempCelsius() > SI7021_MAX_TEMP)
	{
		si7021_coolingDown = true;
		enableBatteryCharger(false);
	}
}

