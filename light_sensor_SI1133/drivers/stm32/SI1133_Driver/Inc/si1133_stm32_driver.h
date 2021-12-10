/*
 *  si1133_stm32_driver.h
 *
 *  A basic library for the Silicon Labs SI1133 UV Index / Ambient Light Sensor
 %  with a I2C interface.
 *
 *  Created on: Dec 4, 2021
 *  Author: George.Howell
 */

#ifndef _SI1133_STM32_DRIVER_H_
#define _SI1133_STM32_DRIVER_H_

/*
 * Includes 
 */

#include <stdlib.h>
#include "si1133.h"
#include "main.h"

/*
 * Type Definitions
 */

typedef struct
{

} SI1133_Config;

typedef enum 
{
  SI1133_STATUS_OK                  = 0x01U,
  SI1133_STATUS_I2C_ERR             = 0x02U,
  SI1133_STATUS_CMMND_CTR_INVCMD    = 0x03U,
  SI1133_STATUS_CMMND_CTR_INVADDR   = 0x04U,
  SI1133_STATUS_CMMND_CTR_ADCERR    = 0x05U,
  SI1133_STATUS_CMMND_CTR_BUFOVER   = 0x06U
} SI1133_StatusDef;

/************************************************************************
 *                              API's
 ************************************************************************/

SI1133_StatusDef SI1133_Init(void);
SI1133_StatusDef SI1133_Read_Sensor(uint16_t* pData);
SI1133_StatusDef SI1133_Read_Register(uint8_t regAddr, uint8_t* pData);
SI1133_StatusDef SI1133_Write_Register(uint8_t regAddr, uint8_t* pData);
SI1133_StatusDef SI1133_Set_Parameter(uint8_t paramAddr, uint8_t paramBitPos, uint8_t paramBits, uint8_t paramOpt);
SI1133_StatusDef SI1133_Write_Parameter(uint8_t paramAddr, uint8_t* pRegData);
SI1133_StatusDef SI1133_Read_Parameter(uint8_t paramAddr, uint8_t* pRegData);

#endif /* _SI1133_STM32_DRIVER_H_ */
