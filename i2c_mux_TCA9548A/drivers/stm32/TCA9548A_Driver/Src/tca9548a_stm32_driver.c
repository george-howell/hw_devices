/*
 *  tca9548a_stm32_driver.h
 *
 *  A basic library for the TI TCA9548a I2C mux.
 *
 *  Created on: Dec 9, 2021
 *  Author: George.Howell
 */

#include "tca9548a_stm32_driver.h"

#define HI2C_INSTANCE                           &hi2c1

/*
 * Private Function Prototypes
 */

/************************************************************************
 *                              API's
 ************************************************************************/

/************************************************************************
 * @fn              - TCA9548A_Read_Ports
 *
 * @brief           - reads the ports returning the command reg for the
 *                    mux
 *
 * @param[in]       - pData: pointer for the returned command register
 *
 * @return          - status
 *
 * @notes           - none
 */
TCA9548A_StatusDef TCA9548A_Read_Ports(uint8_t* pData)
{
    if (HAL_I2C_Master_Receive(HI2C_INSTANCE, TCA9548A_DEV_ADDR, pData, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    return TCA9548A_STATUS_OK; 
}

/************************************************************************
 * @fn              - TCA9548A_Enable_Port
 *
 * @brief           - enables a port without affecting any other port 
 *                    status
 *
 * @param[in]       - port: port number to enable
 *
 * @return          - status
 *
 * @notes           - none
 */
TCA9548A_StatusDef TCA9548A_Enable_Port(uint8_t port)
{
    uint8_t* pData = (uint8_t*)malloc(1);

    if (HAL_I2C_Master_Receive(HI2C_INSTANCE, TCA9548A_DEV_ADDR, pData, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    // set port bit
    *pData |= (1<<port);

    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, TCA9548A_DEV_ADDR, pData, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    free(pData);

    return TCA9548A_STATUS_OK;
}

/************************************************************************
 * @fn              - TCA9548A_Enable_Single_Port
 *
 * @brief           - enables a single port only
 *
 * @param[in]       - port: port number to enable
 *
 * @return          - status
 *
 * @notes           - none
 */
TCA9548A_StatusDef TCA9548A_Enable_Single_Port(uint8_t port)
{
    // set port bit
    port = (1<<port);

    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, TCA9548A_DEV_ADDR, &port, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    return TCA9548A_STATUS_OK;
}

/************************************************************************
 * @fn              - TCA9548A_Disable_Port
 *
 * @brief           - disables a port without affecting any other port 
 *                    status
 *
 * @param[in]       - port: port number to enable
 *
 * @return          - status
 *
 * @notes           - none
 */
TCA9548A_StatusDef TCA9548A_Disable_Port(uint8_t port)
{
    uint8_t* pData = (uint8_t*)malloc(1);

    if (HAL_I2C_Master_Receive(HI2C_INSTANCE, TCA9548A_DEV_ADDR, pData, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    // set port bit
    *pData &= ~(1<<port);

    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, TCA9548A_DEV_ADDR, pData, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    free(pData);

    return TCA9548A_STATUS_OK;
}

/************************************************************************
 * @fn              - TCA9548A_Disable_All_Ports
 *
 * @brief           - disables all ports
 *
 * @param[in]       - 
 *
 * @return          - status
 *
 * @notes           - 
 */
TCA9548A_StatusDef TCA9548A_Disable_All_Ports(void)
{
    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, TCA9548A_DEV_ADDR, 0x00, 1, TCA9548A_I2C_TIMEOUT) != HAL_OK)
    {
        return TCA9548A_STATUS_I2C_ERR;
    }

    return TCA9548A_STATUS_OK;
}

