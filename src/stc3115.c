/**
 * @file			stc3115.c
 * @author			Imanol Gomez
 * @date			23.06.2016
 *
 * @details
 */

/******************** include files ***********************/
#include "stc3115.h"
#include "i2c.h"

/******************** defines *****************************/

/******************** prototypes **************************/

/******************** struct data type ********************/

/******************** private variables********************/

/******************** private function ********************/

/******************** interrupt function ******************/

/******************** global function *********************/


bool stc3115_initialize(void)
{
	stc3115_voltage = 0; // V
	stc3115_current = 0; // A

	return stc3115_enableOperatingMode(true);
}

bool stc3115_testConnection(void)
{
	uint8_t id = stc3115_registerID();
	if(id == STC3115_ID)
		return true;

    return false;
}


uint8_t stc3115_registerID(void)
{
	return readI2C_1Byte(STC3115_SLAVE_ADDRESS,STC3115_REG_ID);
}

bool stc3115_enableOperatingMode(bool enable)
{
	//uint8_t mode = stc3115_getCurrentMode();

	I2C_Write_Def i2c_writeTransfer;
	uint8_t i2c_write_data[1] = {enable ? 0x10 : 0x00};

	i2c_writeTransfer.addr  = STC3115_SLAVE_ADDRESS;
	i2c_writeTransfer.regstr  = STC3115_REG_MODE;
	i2c_writeTransfer.data  = i2c_write_data;
	i2c_writeTransfer.len  = 1;

	bool completed = writeI2C(&i2c_writeTransfer);

	return completed;
}

float stc3115_readVoltage(void)
{
	uint8_t data[2] = {0, 0}; // TO READ
	int vlt = 0;

	I2C_Read_Def i2c_readTransfer;
		uint8_t i2c_read_data[1] = {-1};
	i2c_readTransfer.addr  = STC3115_SLAVE_ADDRESS;
	i2c_readTransfer.regstr  = STC3115_REG_VOLTAGE;
	i2c_readTransfer.read_data = i2c_read_data;
	i2c_readTransfer.read_len  = 1;
	i2c_readTransfer.write_len  = 0;

	bool completed = readI2C(&i2c_readTransfer);

	data[0] = i2c_readTransfer.read_data[0];

	i2c_readTransfer.regstr  = STC3115_REG_VOLTAGE + 1;
	completed = readI2C(&i2c_readTransfer);

	data[1] = i2c_readTransfer.read_data[0];


	vlt = data[1] << 8 | data[0];

	float voltage = 0.00244 * (float)vlt;

	return voltage;
}
float stc3115_readCurrent(void)
{
	uint8_t data[2] = {0, 0}; // TO READ
	uint16_t vlt = 0;
	float sense_resistor = 0.03;
	float voltage_drop;
	float current;

	I2C_Read_Def i2c_readTransfer;
		uint8_t i2c_read_data[1] = {-1};
	i2c_readTransfer.addr  = STC3115_SLAVE_ADDRESS;
	i2c_readTransfer.regstr  = STC3115_REG_CURRENT;
	i2c_readTransfer.read_data = i2c_read_data;
	i2c_readTransfer.read_len  = 1;
	i2c_readTransfer.write_len  = 0;

	bool completed = readI2C(&i2c_readTransfer);

	data[0] = i2c_readTransfer.read_data[0];

	i2c_readTransfer.regstr  = STC3115_REG_CURRENT + 1;
	completed = readI2C(&i2c_readTransfer);

	data[1] = i2c_readTransfer.read_data[0];

	vlt = data[1] << 8 | data[0];
	vlt = ~vlt + 1; // binary code now

	// on the sense resistor
	voltage_drop = 0.000001 * 11.77 * (float)vlt;
	current = voltage_drop / sense_resistor;

	return current;
}

uint8_t stc3115_getCurrentMode()
{
	I2C_Read_Def i2c_readTransfer;
	uint8_t i2c_read_data[1] = {-1};

	i2c_readTransfer.addr  = STC3115_SLAVE_ADDRESS;
	i2c_readTransfer.write_len  = 0;
	i2c_readTransfer.regstr  = STC3115_REG_MODE;
	i2c_readTransfer.read_data = i2c_read_data;
	i2c_readTransfer.read_len  = 1;

	readI2C(&i2c_readTransfer);

	return i2c_readTransfer.read_data[0];
}
