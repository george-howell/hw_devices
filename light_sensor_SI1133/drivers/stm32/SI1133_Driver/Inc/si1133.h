/*
 *  si1133.h
 *
 *  A basic library for the Silicon Labs SI1133 UV Index / Ambient Light Sensor
 %  with a I2C interface.
 *
 *  Created on: Dec 4, 2021
 *  Author: George.Howell
 */

#ifndef _SI1133_H_
#define _SI1133_H_

#define SI1133_I2C_TIMEOUT                      ((uint8_t)0xff)

/*
 * Macros
 */

// I2C Device Address
#define SI1133_DEV_ADDR	                        ((uint8_t)0xAA)     // 8-bit I2C device address

// directly accessible register addresses
#define SI1133_PART_ID_ADDR                     ((uint8_t)0x00)
#define SI1133_REV_ID_ADDR                      ((uint8_t)0x01)
#define SI1133_MFR_ID_ADDR                      ((uint8_t)0x02)
#define SI1133_INFO0_ADDR                       ((uint8_t)0x03)
#define SI1133_INFO1_ADDR                       ((uint8_t)0x04)
#define SI1133_HOSTIN3_ADDR                     ((uint8_t)0x07)
#define SI1133_HOSTIN2_ADDR                     ((uint8_t)0x08)
#define SI1133_HOSTIN1_ADDR                     ((uint8_t)0x09)
#define SI1133_HOSTIN0_ADDR                     ((uint8_t)0x0a)
#define SI1133_COMMAND_ADDR                     ((uint8_t)0x0b)
#define SI1133_IRQ_ENABLE_ADDR                  ((uint8_t)0x0f)
#define SI1133_RESPONSE1_ADDR                   ((uint8_t)0x10)
#define SI1133_RESPONSE0_ADDR                   ((uint8_t)0x11)
#define SI1133_IRQ_STATUS_ADDR                  ((uint8_t)0x12)
#define SI1133_HOSTOUT0_ADDR                    ((uint8_t)0x13)
#define SI1133_HOSTOUT1_ADDR                    ((uint8_t)0x14)
#define SI1133_HOSTOUT2_ADDR                    ((uint8_t)0x15)
#define SI1133_HOSTOUT3_ADDR                    ((uint8_t)0x16)
#define SI1133_HOSTOUT4_ADDR                    ((uint8_t)0x17)
#define SI1133_HOSTOUT5_ADDR                    ((uint8_t)0x18)
#define SI1133_HOSTOUT6_ADDR                    ((uint8_t)0x19)
#define SI1133_HOSTOUT7_ADDR                    ((uint8_t)0x1A)
#define SI1133_HOSTOUT8_ADDR                    ((uint8_t)0x1B)
#define SI1133_HOSTOUT9_ADDR                    ((uint8_t)0x1C)
#define SI1133_HOSTOUT10_ADDR                   ((uint8_t)0x1D)
#define SI1133_HOSTOUT11_ADDR                   ((uint8_t)0x1E)
#define SI1133_HOSTOUT12_ADDR                   ((uint8_t)0x1F)
#define SI1133_HOSTOUT13_ADDR                   ((uint8_t)0x20)
#define SI1133_HOSTOUT14_ADDR                   ((uint8_t)0x21)
#define SI1133_HOSTOUT15_ADDR                   ((uint8_t)0x22)
#define SI1133_HOSTOUT16_ADDR                   ((uint8_t)0x23)
#define SI1133_HOSTOUT17_ADDR                   ((uint8_t)0x24)
#define SI1133_HOSTOUT18_ADDR                   ((uint8_t)0x25)
#define SI1133_HOSTOUT19_ADDR                   ((uint8_t)0x26)
#define SI1133_HOSTOUT20_ADDR                   ((uint8_t)0x27)
#define SI1133_HOSTOUT21_ADDR                   ((uint8_t)0x28)
#define SI1133_HOSTOUT22_ADDR                   ((uint8_t)0x29)
#define SI1133_HOSTOUT23_ADDR                   ((uint8_t)0x2a)
#define SI1133_HOSTOUT24_ADDR                   ((uint8_t)0x2b)
#define SI1133_HOSTOUT25_ADDR                   ((uint8_t)0x2c)

// sub register addresses
#define SI1133_I2C_ADDR_ADDR                    ((uint8_t)0x00)
#define SI1133_CHAN_LIST_ADDR                   ((uint8_t)0x01)
#define SI1133_ADCCONFIG0_ADDR                  ((uint8_t)0x02)
#define SI1133_ADCSENS0_ADDR                    ((uint8_t)0x03)
#define SI1133_ADCPOST0_ADDR                    ((uint8_t)0x04)
#define SI1133_MEASCONFIG0_ADDR                 ((uint8_t)0x05)
#define SI1133_ADCCONFIG1__ADDR                 ((uint8_t)0x06)
#define SI1133_ADCSENS1_ADDR                    ((uint8_t)0x07)
#define SI1133_ADCPOST1_ADDR                    ((uint8_t)0x08)
#define SI1133_MEASCONFIG1_ADDR                 ((uint8_t)0x09)
#define SI1133_ADCCONFIG2__ADDR                 ((uint8_t)0x0a)
#define SI1133_ADCSENS2_ADDR                    ((uint8_t)0x0b)
#define SI1133_ADCPOST2_ADDR                    ((uint8_t)0x0c)
#define SI1133_MEASCONFIG2_ADDR                 ((uint8_t)0x0d)
#define SI1133_ADCCONFIG3__ADDR                 ((uint8_t)0x0e)
#define SI1133_ADCSENS3_ADDR                    ((uint8_t)0x0f)
#define SI1133_ADCPOST3_ADDR                    ((uint8_t)0x10)
#define SI1133_MEASCONFIG3_ADDR                 ((uint8_t)0x11)
#define SI1133_ADCCONFIG4__ADDR                 ((uint8_t)0x12)
#define SI1133_ADCSENS4_ADDR                    ((uint8_t)0x13)
#define SI1133_ADCPOST4_ADDR                    ((uint8_t)0x14)
#define SI1133_MEASCONFIG4_ADDR                 ((uint8_t)0x15)
#define SI1133_ADCCONFIG5__ADDR                 ((uint8_t)0x16)
#define SI1133_ADCSENS5_ADDR                    ((uint8_t)0x17)
#define SI1133_ADCPOST5_ADDR                    ((uint8_t)0x18)
#define SI1133_MEASCONFIG5_ADDR                 ((uint8_t)0x19)
#define SI1133_MEASRATE_H_ADDR                  ((uint8_t)0x1a)
#define SI1133_MEASRATE_L_ADDR                  ((uint8_t)0x1b)
#define SI1133_MEASCOUNT0_ADDR                  ((uint8_t)0x1c)
#define SI1133_MEASCOUNT1_ADDR                  ((uint8_t)0x1d)
#define SI1133_MEASCOUNT2_ADDR                  ((uint8_t)0x1e)
#define SI1133_THRESHOLD0_H_ADDR                ((uint8_t)0x25)
#define SI1133_THRESHOLD0_L_ADDR                ((uint8_t)0x26)
#define SI1133_THRESHOLD1_H_ADDR                ((uint8_t)0x27)
#define SI1133_THRESHOLD1_L_ADDR                ((uint8_t)0x28)
#define SI1133_THRESHOLD2_H_ADDR                ((uint8_t)0x29)
#define SI1133_THRESHOLD2_L_ADDR                ((uint8_t)0x2a)
#define SI1133_BURST_ADDR                       ((uint8_t)0x2b)

/*
 * @RESPONSE0 Register
 */

// RESPONSE0 Register Bit Position
#define SI1133_RESPONSE0_RUNNING_BP             ((uint8_t)0x07)
#define SI1133_RESPONSE0_SUSPEND_BP             ((uint8_t)0x06)
#define SI1133_RESPONSE0_SLEEP_BP               ((uint8_t)0x05)
#define SI1133_RESPONSE0_CMD_ERR_BP             ((uint8_t)0x04)
#define SI1133_RESPONSE0_CMMND_CTR_BP           ((uint8_t)0x00)

// RESPONSE0 Register No. of Bits
#define SI1133_RESPONSE0_RUNNING_BITS           ((uint8_t)0x01)
#define SI1133_RESPONSE0_SUSPEND_BITS           ((uint8_t)0x01)
#define SI1133_RESPONSE0_SLEEP_BITS             ((uint8_t)0x01)
#define SI1133_RESPONSE0_CMD_ERR_BITS           ((uint8_t)0x01)
#define SI1133_RESPONSE0_CMMND_CTR_BITS         ((uint8_t)0x0f)

// RESPONSE0 RUNNING, SUSPEND, SLEEP Registers
#define SI1133_RESPONSE0_DI                     ((uint8_t)0x00)
#define SI1133_RESPONSE0_EN                     ((uint8_t)0x01)

// RESPONSE0 CMD_ERR Register
#define SI1133_RESPONSE0_CMD_ERR_CNT            ((uint8_t)0x00)
#define SI1133_RESPONSE0_CMD_ERR_ERR            ((uint8_t)0x01)

// RESPONSE0 CMMND_CTR Register
#define SI1133_RESPONSE0_CMMND_CTR_INVCMD       ((uint8_t)0x10)
#define SI1133_RESPONSE0_CMMND_CTR_INVADDR      ((uint8_t)0x11)
#define SI1133_RESPONSE0_CMMND_CTR_ADCERR       ((uint8_t)0x12)
#define SI1133_RESPONSE0_CMMND_CTR_BUFOVER      ((uint8_t)0x13)

/*
 * @ADCCONFIGx Register
 */

// ADCCONFIGx Register Bit Position
#define SI1133_ADCCONFIGx_DECIM_RATE_BP         ((uint8_t)0x05)
#define SI1133_ADCCONFIGx_ADCMUX_BP             ((uint8_t)0x00)

// ADCCONFIGx Register Bits
#define SI1133_ADCCONFIGx_DECIM_RATE_BITS       ((uint8_t)0x03)
#define SI1133_ADCCONFIGx_ADCMUX_BITS           ((uint8_t)0x1F)

// ADCCONFIGx DECIM_RATE Register
#define SI1133_ADCCONFIGx_DECIM_RATE_1024       ((uint8_t)0x00)
#define SI1133_ADCCONFIGx_DECIM_RATE_2048       ((uint8_t)0x01)
#define SI1133_ADCCONFIGx_DECIM_RATE_4096       ((uint8_t)0x02)
#define SI1133_ADCCONFIGx_DECIM_RATE_512        ((uint8_t)0x03)

// ADCCONFIGx ADCMUX Register
#define SI1133_ADCCONFIGx_ADCMUX_SMALL_IR       ((uint8_t)0x00)
#define SI1133_ADCCONFIGx_ADCMUX_MED_IR         ((uint8_t)0x01)
#define SI1133_ADCCONFIGx_ADCMUX_LARGE_IR       ((uint8_t)0x02)
#define SI1133_ADCCONFIGx_ADCMUX_WHITE          ((uint8_t)0x0b)
#define SI1133_ADCCONFIGx_ADCMUX_LARGE_WHITE    ((uint8_t)0x0d)
#define SI1133_ADCCONFIGx_ADCMUX_UV             ((uint8_t)0x18)
#define SI1133_ADCCONFIGx_ADCMUX_UV_DEEP        ((uint8_t)0x19)

/*
 * @ADCSENSx Register
 */

// ADCSENSx Register Bit Position
#define SI1133_ADCSENSx_HSIG_BP                 ((uint8_t)0x07)
#define SI1133_ADCSENSx_SW_GAIN_BP              ((uint8_t)0x04)
#define SI1133_ADCSENSx_HW_GAIN_BP              ((uint8_t)0x00)

// ADCSENSx Register Bits
#define SI1133_ADCSENSx_HSIG_BITS               ((uint8_t)0x01)
#define SI1133_ADCSENSx_SW_GAIN_BITS            ((uint8_t)0x07)
#define SI1133_ADCSENSx_HW_GAIN_BITS            ((uint8_t)0x0F)

// ADCSENSx HSIG Register
#define SI1133_ADCSENSx_HSIG_NORM_GAIN          ((uint8_t)0x00)
#define SI1133_ADCSENSx_HSIG_HIGH_GAIN          ((uint8_t)0x01)

// ADCSENSx SW_GAIN Register
#define SI1133_ADCSENSx_SW_GAIN_1               ((uint8_t)0x00)
#define SI1133_ADCSENSx_SW_GAIN_2               ((uint8_t)0x01)
#define SI1133_ADCSENSx_SW_GAIN_4               ((uint8_t)0x02)
#define SI1133_ADCSENSx_SW_GAIN_8               ((uint8_t)0x03)
#define SI1133_ADCSENSx_SW_GAIN_16              ((uint8_t)0x04)
#define SI1133_ADCSENSx_SW_GAIN_32              ((uint8_t)0x05)
#define SI1133_ADCSENSx_SW_GAIN_64              ((uint8_t)0x06)
#define SI1133_ADCSENSx_SW_GAIN_128             ((uint8_t)0x07)

// ADCSENSx HW_GAIN Register
#define SI1133_ADCSENSx_HW_GAIN_0               ((uint8_t)0x00)
#define SI1133_ADCSENSx_HW_GAIN_1               ((uint8_t)0x01)
#define SI1133_ADCSENSx_HW_GAIN_2               ((uint8_t)0x02)
#define SI1133_ADCSENSx_HW_GAIN_3               ((uint8_t)0x03)
#define SI1133_ADCSENSx_HW_GAIN_4               ((uint8_t)0x04)
#define SI1133_ADCSENSx_HW_GAIN_5               ((uint8_t)0x05)
#define SI1133_ADCSENSx_HW_GAIN_6               ((uint8_t)0x06)
#define SI1133_ADCSENSx_HW_GAIN_7               ((uint8_t)0x07)
#define SI1133_ADCSENSx_HW_GAIN_8               ((uint8_t)0x08)
#define SI1133_ADCSENSx_HW_GAIN_9               ((uint8_t)0x09)
#define SI1133_ADCSENSx_HW_GAIN_10              ((uint8_t)0x0a)
#define SI1133_ADCSENSx_HW_GAIN_11              ((uint8_t)0x0b)

/*
 * @ADCPOSTx Register
 */


/*
 * @MEASCONFIGx Register
 */


/*
 * Main Commands
 */
#define SI1133_COMMAND_RST_CMD_CTR              ((uint8_t)0x00)
#define SI1133_COMMAND_RST_SW                   ((uint8_t)0x01)
#define SI1133_COMMAND_FORCE                    ((uint8_t)0x11)
#define SI1133_COMMAND_PAUSE                    ((uint8_t)0x12)
#define SI1133_COMMAND_START                    ((uint8_t)0x13)
#define SI1133_COMMAND_PARAM_QUERY              ((uint8_t)0x40)
#define SI1133_COMMAND_PARAM_SET                ((uint8_t)0x80)

#endif /* _SI1133_H_ */
