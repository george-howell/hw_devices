/*
 *  tca9548a_stm32_driver.h
 *
 *  A basic library for the TI TCA9548a I2C mux.
 *
 *  Created on: Dec 9, 2021
 *  Author: George.Howell
 */

#ifndef _TCA9548A_STM32_DRIVER_H_
#define _TCA9548A_STM32_DRIVER_H_

/*
 * Includes 
 */

#include <stdint.h>
#include <stdlib.h>
#include "main.h"
#include "tca9548a.h"
#include "stm32f4xx_hal.h"

/*
 * Type Definitions
 */

typedef enum 
{
  TCA9548A_STATUS_OK                = 0x01U,
  TCA9548A_STATUS_I2C_ERR           = 0x02U
} TCA9548A_StatusDef;

/************************************************************************
 *                              API's
 ************************************************************************/

TCA9548A_StatusDef TCA9548A_Read_Ports(uint8_t* pData);
TCA9548A_StatusDef TCA9548A_Enable_Port(uint8_t port);
TCA9548A_StatusDef TCA9548A_Enable_Single_Port(uint8_t port);
TCA9548A_StatusDef TCA9548A_Disable_Port(uint8_t port);
TCA9548A_StatusDef TCA9548A_Disable_All_Ports(void);

#endif /* _TCA9548A_STM32_DRIVER_H_ */
