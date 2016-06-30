/**
 * @file			i2c.h
 * @author			grli
 * @date			01.03.2016
 *	
 * @details
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <stdbool.h>

#include "em_i2c.h"
#include "em_gpio.h"

#define I2C_TRANSFER_TIMEOUT 300000

typedef struct
{
  /**
   * @brief
   *   Address to use after (repeated) start.
   * @details
   *   Layout details, A = address bit, X = don't care bit (set to 0):
   *   @li 7 bit address - use format AAAA AAAX.
   *   @li 10 bit address - use format XXXX XAAX AAAA AAAA
   */
  uint16_t addr;

  uint8_t regstr;

  uint8_t  *data;

  uint16_t len;

} I2C_Write_Def;

typedef struct
{
  /**
   * @brief
   *   Address to use after (repeated) start.
   * @details
   *   Layout details, A = address bit, X = don't care bit (set to 0):
   *   @li 7 bit address - use format AAAA AAAX.
   *   @li 10 bit address - use format XXXX XAAX AAAA AAAA
   */
  uint16_t addr;

  uint8_t regstr;

  uint8_t  *read_data;

  uint16_t read_len;

  uint8_t  *write_data;

  uint16_t write_len;

} I2C_Read_Def;



/**
 *
 */
bool processI2C(I2C_TransferSeq_TypeDef* i2cTransfer);

/**
 *
 */
void setupI2C(void);

/**
 *
 */
void testI2C(void);

/**
 *
 */
bool writeI2C(I2C_Write_Def*  writeTransfer);

/**
 *
 */
bool readI2C(I2C_Read_Def*  readTransfer);


/**
 *
 */
bool writeI2C_1Byte(uint16_t addr,  uint8_t regstr,  uint8_t  data);

/**
 *
 */
uint8_t readI2C_1Byte(uint16_t addr,  uint8_t regstr);



#endif /* I2C_H_ */
