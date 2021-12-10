/*
 *
 */

#ifndef _SHT21_DRIVER_C_
#define _SHT21_DRIVER_C_

#include "sht21_stm32_driver.h"

/*
 * Private API Prototypes
 */

float convertToTemp(uint16_t data);
float convertToRH(uint16_t data);

/*
 * API's
 */

HAL_StatusTypeDef sht21_init(SHT21_UReg_Config_t sht21Cfg)
{
	// collate into full user reg data
	uint8_t tmpVal = sht21Cfg.measRes;
	tmpVal |= sht21Cfg.heater;
	tmpVal |= sht21Cfg.otpReload;

	return sht21_writeUserReg(tmpVal);
}

/************************************************************************
 * @fn				- sht21_trigMeas
 *
 * @brief			- triggers a temperature and / or relative humidity
 * 					  measurement
 *
 * @param[in]		- base address of the GPIO peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @notes 			- none
 */
HAL_StatusTypeDef sht21_trigMeas(uint8_t command)
{
	return HAL_I2C_Master_Transmit(HI2C, SHT21_DEV_ADDR, &command, 1, SH21_I2C_TIMEOUT);
}

/************************************************************************
 * @fn				- sht21_readData
 *
 * @brief			- triggers a temperature and / or relative humidity
 * 					  measurement
 *
 * @param[in]		- base address of the GPIO peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @notes 			- none
 */
HAL_StatusTypeDef sht21_readData(uint8_t command, float *val)
{
	uint8_t *pData = (uint8_t*)malloc(2);

	// read data
	HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(HI2C, SHT21_DEV_ADDR, pData, 2, SH21_I2C_TIMEOUT);
	if (ret != HAL_OK)
	{
		return ret;
	}

	// convert to uint16_t
	uint16_t data16;
	data16 = (*pData) << 8;
	data16 |= *(pData+1);

	// free pointer
	free(pData);

	// convert to temp / rh value
	if (command == SHT21_TRIG_T_MEAS_HM || command == SHT21_TRIG_T_MEAS_NHM)
	{
		*val = convertToTemp(data16);
	}
	else
	{
		*val = convertToRH(data16);
	}

	return ret;
}

/************************************************************************
 * @fn				- sht21_trigReadData
 *
 * @brief			- triggers a temperature and / or relative humidity
 * 					  measurement
 *
 * @param[in]		- base address of the GPIO peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @notes 			- none
 */
HAL_StatusTypeDef sht21_trigReadData(uint8_t command, float *val)
{
	HAL_StatusTypeDef ret;

	// send command
	ret = sht21_trigMeas(command);
	if (ret != HAL_OK)
	{
		return ret;
	}

	// delay for measurement to process
	for(uint32_t ni=0; ni<500000; ni++);

	// read data
	ret = sht21_readData(command, val);
	
	return ret;
}

/************************************************************************
 * @fn				- sht21_readUserReg
 *
 * @brief			- triggers a temperature and / or relative humidity
 * 					  measurement
 *
 * @param[in]		- base address of the GPIO peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @notes 			- none
 */
HAL_StatusTypeDef sht21_readUserReg(uint8_t userRegRead, uint8_t *pUserRegData)
{
    // write read user reg request
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(HI2C, SHT21_DEV_ADDR, (uint8_t*)SHT21_READ_USER_REG, 1, SH21_I2C_TIMEOUT);
    if (ret != HAL_OK)
    {
        return ret;
    }

    // read user reg data
    ret = HAL_I2C_Master_Receive(HI2C, SHT21_DEV_ADDR, pUserRegData, 1, SH21_I2C_TIMEOUT);
    if (ret != HAL_OK)
    {
        return ret;
    }

    // return pointer for only the parmeters selected
    *pUserRegData &= userRegRead;

    return ret;
}

/************************************************************************
 * @fn				- sht21_writeUserReg
 *
 * @brief			- triggers a temperature and / or relative humidity
 * 					  measurement
 *
 * @param[in]		- base address of the GPIO peripheral
 * @param[in]		- ENABLE or DISABLE macros
 *
 * @return			- none
 *
 * @notes 			- none
 */
HAL_StatusTypeDef sht21_writeUserReg(uint8_t uRegSetting)
{
    // send read user reg request
    HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(HI2C, SHT21_DEV_ADDR, (uint8_t*)SHT21_READ_USER_REG, 1, SH21_I2C_TIMEOUT);
    if (ret != HAL_OK)
    {
        return ret;
    }

    // read user reg data
    uint8_t* pUserReg = (uint8_t*)malloc(2);

    ret = HAL_I2C_Master_Receive(HI2C, SHT21_DEV_ADDR, pUserReg, 1, SH21_I2C_TIMEOUT);
    if (ret != HAL_OK)
    {
        return ret;
    }

    // reset and apply setting
    uint8_t regValTmp;
    if (uRegSetting == SHT21_UREG_MEASRES_RH12_T14 || uRegSetting == SHT21_UREG_MEASRES_RH8_T12 || uRegSetting == SHT21_UREG_MEASRES_RH10_T13 || uRegSetting == SHT21_UREG_MEASRES_RH11_T11)
    {
    	regValTmp = SHT21_UREG_MEASRES;
    } else if (uRegSetting==SHT21_UREG_HEATER_DI || uRegSetting==SHT21_UREG_HEATER_EN)
    {
    	regValTmp = SHT21_UREG_HEATER;
    } else if (uRegSetting==SHT21_UREG_OTPRELOAD_EN || uRegSetting==SHT21_UREG_OTPRELOAD_DI)
    {
    	regValTmp = SHT21_UREG_OTPRELOAD;
    } else
    {
    	regValTmp = SHT21_UREG_ALL;
    }

    *pUserReg &= ~(regValTmp);
    *pUserReg |= uRegSetting;

    // add user reg to end
    *(pUserReg+1) = *pUserReg;
    *pUserReg = SHT21_WRITE_USER_REG;

    // write new user reg data
    ret = HAL_I2C_Master_Transmit(HI2C, SHT21_DEV_ADDR, pUserReg, 2, SH21_I2C_TIMEOUT);
    if (ret != HAL_OK)
    {
        return ret;
    }

    free(pUserReg);

    return ret;
}

/*
 * Private API's
 */

// converts the read data to a temperature reading
float convertToTemp(uint16_t data)
{
	return (-46.85 + 175.72 * ((float)data/65536));
}

// converts the read data to a relative humidity reading
float convertToRH(uint16_t data)
{
	return (-6 + 125 * ((float)data/65536));
}

#endif /* _SHT21_DRIVER_C_ */
