/**
 * @file			i2c.c
 * @author			Imanol Gomez
 * @date			13.06.2016
 *	
 * @details
 */

/******************** include files ***********************/
#include "time_utils.h"
#include "stc3105.h"
#include "stc3115.h"
#include "si7021.h"
#include "mpu9250.h"
#include "adp8866.h"
#include "device_utils.h"

#include "i2c.h"

/******************** defines *****************************/

/******************** prototypes **************************/

/******************** struct data type ********************/

/******************** private variables********************/

/******************** private function ********************/

/******************** interrupt function ******************/

/******************** global function *********************/
void setupI2C(void)
{
  // Using default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  /* Using PC0 (SDA) and PC1 (SCL) */
  GPIO_PinModeSet(gpioPortA, 0, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(gpioPortA, 1, gpioModeWiredAndPullUpFilter, 1);


  //GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0);
  //GPIO_PinModeSet(gpioPortB, 12, gpioModePushPull, 0);



    /* Enable pins at location 1 */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                I2C_ROUTE_LOCATION_LOC0;

  /* Initializing the I2C */
  I2C_Init(I2C0, &i2cInit);
}


/**************************************************************************//**
 * @brief Test I2C bus for all components
 * @detail it glows green if it is successful or red if not
 *****************************************************************************/
void testI2C()
{
	bool bConnection = true;
	int revision = getFirmwareVersion();
	float vlt = 0.0;
	adp8866_isInitialized = false;


	bConnection = bConnection && stc_testConnection();
	bConnection = bConnection && stc_initialize();
	bConnection = bConnection && si7201_testConnection();
	bConnection = bConnection && mpu9250_testConnection();
	bConnection = bConnection && mpu9250_initialize();

	vlt = stc_readVoltage();
	//if(vlt < BATTERY_EIGHTH){
		//return;
	//}

	bConnection = bConnection && adp8866_testConnection();
	bConnection = bConnection && adp8866_initialize();

	float temp = si7021_getTempCelsius();

	int ledID = 2;
	uint32_t delay = 500;

	//GPIO_PinOutClear(gpioPortE, 12); // Set to 0
	//Delay(5*delay);
	//GPIO_PinOutSet(gpioPortE, 12); // Set to 1

	adp8866_set_all_black();

	if(bConnection){
		adp8866_set_led_red(ledID);
		Delay3(delay);
		adp8866_set_led_green(ledID);
		Delay3(delay);
		adp8866_set_led_blue(ledID);
		Delay3(delay);
	}
	else{
		adp8866_set_led_red(ledID);
		Delay3(delay);
	}

	adp8866_set_all_black();
}



bool processI2C(I2C_TransferSeq_TypeDef* i2cTransfer)
{

  uint32_t timeout = I2C_TRANSFER_TIMEOUT;
  I2C_TransferReturn_TypeDef ret = I2C_TransferInit(I2C0, i2cTransfer);

  /* Sending data */
  ret = I2C_Transfer(I2C0);
  while (ret == i2cTransferInProgress && timeout--)
	  ret = I2C_Transfer(I2C0);


  if(ret == i2cTransferDone){
	  return true;
  }

  return false;
}



bool writeI2C(I2C_Write_Def*  writeTransfer)
{
	I2C_TransferSeq_TypeDef i2cTransfer;

	i2cTransfer.addr  = writeTransfer->addr;
	i2cTransfer.flags = I2C_FLAG_WRITE;
	uint8_t i2c_write_data[writeTransfer->len+1];
	i2c_write_data[0] = writeTransfer->regstr;
	for(int i = 0; i < writeTransfer->len; i++)
	{
		i2c_write_data[i+1] = writeTransfer->data[i];
	}

	i2cTransfer.buf[0].data  = i2c_write_data;
	i2cTransfer.buf[0].len    = writeTransfer->len+1;

	return processI2C(&i2cTransfer);
}

bool readI2C(I2C_Read_Def*  readTransfer)
{
	I2C_TransferSeq_TypeDef i2cTransfer;
	uint8_t i2c_write_data[readTransfer->write_len+1];
	i2c_write_data[0] = readTransfer->regstr;
	for(int i = 0; i < readTransfer->write_len; i++)
	{
		i2c_write_data[i+1] = readTransfer->write_data[i];
	}

	i2cTransfer.addr  = readTransfer->addr;
	i2cTransfer.flags = I2C_FLAG_WRITE_READ;
	i2cTransfer.buf[0].data   = i2c_write_data;
	i2cTransfer.buf[0].len    = readTransfer->write_len+1;
	i2cTransfer.buf[1].data    = readTransfer->read_data;
	i2cTransfer.buf[1].len    = readTransfer->read_len;

	bool completed =  processI2C(&i2cTransfer);

	return completed;
}

bool writeI2C_1Byte(uint16_t addr,  uint8_t regstr,  uint8_t  data)
{
	I2C_TransferSeq_TypeDef i2cTransfer;

	i2cTransfer.addr  = addr;
	i2cTransfer.flags = I2C_FLAG_WRITE;

	uint8_t i2c_write_data[2];
	i2c_write_data[0] = regstr;
	i2c_write_data[1] = data;

	i2cTransfer.buf[0].data  = i2c_write_data;
	i2cTransfer.buf[0].len    = 2;

	return processI2C(&i2cTransfer);
}

uint8_t readI2C_1Byte(uint16_t addr,  uint8_t regstr)
{
	I2C_TransferSeq_TypeDef i2cTransfer;
	uint8_t read_data[1] = {-1};

	i2cTransfer.addr  = addr;
	i2cTransfer.flags = I2C_FLAG_WRITE_READ;

	uint8_t i2c_write_data[2];
	i2c_write_data[0] = regstr;

	i2cTransfer.buf[0].data  = i2c_write_data;
	i2cTransfer.buf[0].len    = 1;
	i2cTransfer.buf[1].data  = read_data;
	i2cTransfer.buf[1].len    = 1;

	processI2C(&i2cTransfer);

	return read_data[0];
}

