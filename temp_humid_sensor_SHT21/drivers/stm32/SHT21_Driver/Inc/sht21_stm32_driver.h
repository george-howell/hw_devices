/*
 *
 */

#ifndef _SHT21_DRIVER_H_
#define _SHT21_DRIVER_H_

/*
 * Includes
 */

#include <stdlib.h>
#include "sht21.h"
#include "sht21_stm32_config.h"
#include "stm32f4xx_hal_i2c.h"

/*
 * Typedef
 */

typedef struct
{
	uint8_t measRes;
	uint8_t heater;
	uint8_t otpReload;
}SHT21_UReg_Config_t;

/*
 * API's
 */

HAL_StatusTypeDef sht21_init(SHT21_UReg_Config_t sht21Cfg);
HAL_StatusTypeDef sht21_trigMeas(uint8_t command);
HAL_StatusTypeDef sht21_readData(uint8_t command, float *val);
HAL_StatusTypeDef sht21_trigReadData(uint8_t command, float *val);
HAL_StatusTypeDef sht21_readUserReg(uint8_t userRegRead, uint8_t *pUserRegData);
HAL_StatusTypeDef sht21_writeUserReg(uint8_t uRegSetting);

#endif /* _SHT21_DRIVER_H_ */
