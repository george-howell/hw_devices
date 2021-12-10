/*
 *  si1133.h
 *
 *  A basic library for the Silicon Labs SI1133 UV Index / Ambient Light Sensor
 %  with a I2C interface.
 *
 *  Created on: Dec 4, 2021
 *  Author: George.Howell
 */

#include "si1133_stm32_driver.h"

#define HI2C_INSTANCE                           &hi2c1

/*
 * Private Function Prototypes
 */

static SI1133_StatusDef SI1133_Read_Response0(uint8_t* count);

/************************************************************************
 *                              API's
 ************************************************************************/

/************************************************************************
 * @fn              - SI1133_Init
 *
 * @brief           - initialises the sensor
 *
 * @param[in]       - 
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Init(void)
{
    SI1133_StatusDef retStatus;

    /* 
     *  ADCCONFIG0 
    */

    // set adc mux
    if ((retStatus = SI1133_Set_Parameter(SI1133_ADCCONFIG0_ADDR, SI1133_ADCCONFIGx_ADCMUX_BP, SI1133_ADCCONFIGx_ADCMUX_BITS, SI1133_ADCCONFIGx_ADCMUX_WHITE)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    /* 
     *  ADCSENS0 
    */

    // set sw gain
    if ((retStatus = SI1133_Set_Parameter(SI1133_ADCSENS0_ADDR, SI1133_ADCSENSx_SW_GAIN_BP, SI1133_ADCSENSx_SW_GAIN_BITS, SI1133_ADCSENSx_SW_GAIN_32)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    /*
     * CHAN_LIST
     */
    if ((retStatus = SI1133_Set_Parameter(SI1133_CHAN_LIST_ADDR, 0x00, 0x3f, 0x01)) != SI1133_STATUS_OK)
	{
		return retStatus;
	}

    return SI1133_STATUS_OK;
}

/************************************************************************
 * @fn              - SI1133_Read_Sensor
 *
 * @brief           - sets a parameter by reading and clearing the value first
 *
 * @param[in]       - 
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Read_Sensor(uint16_t* pData)
{
    SI1133_StatusDef retStatus;

    // force sensor reading
    uint8_t cmdTmp = SI1133_COMMAND_FORCE;
    if ((retStatus = SI1133_Write_Register(SI1133_COMMAND_ADDR, &cmdTmp)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // pause to let sensor capture measurement
    for (uint32_t ni=0; ni<500000; ni++);

    // read HOSTOUT0 register (for MSB)
    uint8_t* pDataTmp = (uint8_t*)malloc(2);

    if ((retStatus = SI1133_Read_Register(SI1133_HOSTOUT0_ADDR, pDataTmp)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // read HOSTOUT1 register (for LSB)
    if ((retStatus = SI1133_Read_Register(SI1133_HOSTOUT1_ADDR, pDataTmp+1)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // combine byte values
    *pData = (*pDataTmp)<<8;
    *pData |= *(pDataTmp+1);

    free(pDataTmp);

    return SI1133_STATUS_OK;
}

/************************************************************************
 * @fn              - SI1133_Read_Register
 *
 * @brief           - reads I2C registers
 *
 * @param[in]       - pRegAddr: pointer to the register address
 * @param[in]       - pData: pointer to the read data
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Read_Register(uint8_t regAddr, uint8_t* pData)
{
    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, SI1133_DEV_ADDR, &regAddr, 1, SI1133_I2C_TIMEOUT) != HAL_OK)
    {
        return SI1133_STATUS_I2C_ERR;
    }

    if (HAL_I2C_Master_Receive(HI2C_INSTANCE, SI1133_DEV_ADDR, pData, 1, SI1133_I2C_TIMEOUT) != HAL_OK)
    {
        return SI1133_STATUS_I2C_ERR;
    }

    return SI1133_STATUS_OK;
}

/************************************************************************
 * @fn              - SI1133_Write_Register
 *
 * @brief           - reads I2C registers
 *
 * @param[in]       - pRegAddr: pointer to the register address
 * @param[in]       - pData: pointer to the data to write
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Write_Register(uint8_t regAddr, uint8_t* pData)
{
    // create address and data pointer
    uint8_t* pTmp = (uint8_t*)malloc(2);
    *pTmp = regAddr;
    *(pTmp+1) = *pData;

    // write data to register
    if (HAL_I2C_Master_Transmit(HI2C_INSTANCE, SI1133_DEV_ADDR, pTmp, 2, SI1133_I2C_TIMEOUT) != HAL_OK)
    {
        return SI1133_STATUS_I2C_ERR;
    }

    free(pTmp);

    return SI1133_STATUS_OK;
}

/************************************************************************
 * @fn              - si1133_set_parameter
 *
 * @brief           - sets a parameter by reading and clearing the value first
 *
 * @param[in]       - 
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Set_Parameter(uint8_t paramAddr, uint8_t paramBitPos, uint8_t paramBits, uint8_t paramOpt)
{
    SI1133_StatusDef retStatus;
    uint8_t* pData = (uint8_t*)malloc(1);

    // read parameter register
    if ((retStatus = SI1133_Read_Parameter(paramAddr, pData)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // clear and set
    *pData &= ~(paramBits << paramBitPos);
    *pData |= (paramOpt << paramBitPos);

    // write to parameter register
    if ((retStatus = SI1133_Write_Parameter(paramAddr, pData)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    free(pData);

    return SI1133_STATUS_OK;
}

/************************************************************************
 * @fn              - SI1133_Write_Parameter
 *
 * @brief           - writes data to an parameter register
 *
 * @param[in]       - paramAddr: parameter address
 * @param[in]       - pRegData: pointer to parameter register data
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Write_Parameter(uint8_t paramAddr, uint8_t* pRegData)
{
    SI1133_StatusDef retStatus;
    uint8_t *count = (uint8_t*)malloc(1);
    uint8_t countTmp;

    // read RESPONSE0 register
    if ((retStatus = SI1133_Read_Response0(count)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // save count value
    countTmp = *count;

    // write data to INPUT0 register
    if ((retStatus = SI1133_Write_Register(SI1133_HOSTIN0_ADDR, pRegData)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // write parameter address to COMMAND register
    paramAddr |= SI1133_COMMAND_PARAM_SET;
    if ((retStatus = SI1133_Write_Register(SI1133_COMMAND_ADDR, &paramAddr)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // read response0 register until count register changes
    while (countTmp == *count)
    {
        // read reg
        if ((retStatus = SI1133_Read_Response0(count)) != SI1133_STATUS_OK)
        {
            return retStatus;
        }
    }

    free(count);

    return SI1133_STATUS_OK;
}


/************************************************************************
 * @fn              - si1133_read_parameter
 *
 * @brief           - reads data in a parameter register
 *
 * @param[in]       - paramAddr: parameter address
 * @param[in]       - pRegData: pointer to parameter register data
 *
 * @return          - status
 *
 * @notes           - none
 */
SI1133_StatusDef SI1133_Read_Parameter(uint8_t paramAddr, uint8_t* pRegData)
{
    SI1133_StatusDef retStatus;
    uint8_t *count = (uint8_t*)malloc(1);
    uint8_t countTmp;

    // read RESPONSE0 register
    if ((retStatus = SI1133_Read_Response0(count)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // save count value
    countTmp = *count;

    // write parameter address to COMMAND register
    paramAddr |= SI1133_COMMAND_PARAM_QUERY;
    if ((retStatus = SI1133_Write_Register(SI1133_COMMAND_ADDR, &paramAddr)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // read response0 register until count register changes
    while (countTmp == *count)
    {
        // read reg
        if ((retStatus = SI1133_Read_Response0(count)) != SI1133_STATUS_OK)
        {
            return retStatus;
        }
    }

    // read from RESPONSE1 register address
    if ((retStatus = SI1133_Read_Register(SI1133_RESPONSE1_ADDR, pRegData)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    free(count);

    return SI1133_STATUS_OK;
}

/************************************************************************
 *                           Private Functions
 ************************************************************************/

/************************************************************************
 * @fn              - SI1133_Read_Response0
 *
 * @brief           - reads data in the RESPONSE0 register
 *
 * @param[in]       - count: ppinter to count value
 *
 * @return          - status
 *
 * @notes           - none
 */
static SI1133_StatusDef SI1133_Read_Response0(uint8_t* count)
{
    SI1133_StatusDef retStatus;
    uint8_t *pData = (uint8_t*)malloc(1);

    // read RESPONSE0 data
    if ((retStatus = SI1133_Read_Register(SI1133_RESPONSE0_ADDR, pData)) != SI1133_STATUS_OK)
    {
        return retStatus;
    }

    // get command control data
    uint8_t cmmndCtr = (*pData>>SI1133_RESPONSE0_CMMND_CTR_BP & SI1133_RESPONSE0_CMMND_CTR_BITS);

    // check CMD_ERR register for error
    if ((*pData>>SI1133_RESPONSE0_CMD_ERR_BP & SI1133_RESPONSE0_CMD_ERR_BITS) == SI1133_RESPONSE0_CMD_ERR_ERR)
    {
        if (cmmndCtr == SI1133_RESPONSE0_CMMND_CTR_INVCMD)
        {
            return SI1133_STATUS_CMMND_CTR_INVCMD;
        } 
        else if (cmmndCtr == SI1133_RESPONSE0_CMMND_CTR_INVADDR)
        {
            return SI1133_STATUS_CMMND_CTR_INVADDR;
        } 
        else if (cmmndCtr == SI1133_RESPONSE0_CMMND_CTR_ADCERR)
        {
            return SI1133_STATUS_CMMND_CTR_ADCERR;
        } 
        else if (cmmndCtr == SI1133_RESPONSE0_CMMND_CTR_BUFOVER)
        {
            return SI1133_STATUS_CMMND_CTR_BUFOVER;
        }       
    }

    free(pData);

    *count = cmmndCtr;

    return SI1133_STATUS_OK;

}

