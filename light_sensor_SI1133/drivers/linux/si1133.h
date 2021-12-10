#ifndef __SI1133_H__
#define __SI1133_H__

// main addresses
#define MAIN_CMD 				((uint8_t)0x0b)
#define MAIN_RESP0 				((uint8_t)0x11)
#define MAIN_RESP1 				((uint8_t)0x10)
#define MAIN_INPUT0				((uint8_t)0x0a)
#define MAIN_HOSTOUT0			((uint8_t)0x13)
#define MAIN_HOSTOUT1			((uint8_t)0x14)
#define MAIN_HOSTOUT2			((uint8_t)0x15)

// main commands
#define FORCE					((uint8_t)0x11)
#define PARAM_QUERY				((uint8_t)0x40)
#define PARAM_SET				((uint8_t)0x80)

// main bits values
#define MAIN_CMD_CTL_BITS		((uint8_t)0x0f)
#define MAIN_CMD_ERR			4
#define MAIN_CMD_ERR_BITS		((uint8_t)0x01)

// sub addresses
#define SUB_CHAN_LIST 			((uint8_t)0x01)
#define SUB_ADCCONFIG0			((uint8_t)0x02)
#define SUB_ADCSENS0			((uint8_t)0x03)
#define SUB_ADCPOST0			((uint8_t)0x04)
#define SUB_MEASCONFIG0			((uint8_t)0x05)

// sub address bits
#define SUB_DECIM_RATE			5
#define SUB_DECIM_RATE_BITS		((uint8_t)0x03)
#define SUB_ADCMUX				0
#define SUB_ADCMUX_BITS			((uint8_t)0x1f)
#define SUB_HSIG				7
#define SUB_HSIG_BITS			((uint8_t)0x01)
#define SUB_SW_GAIN				4
#define SUB_SW_GAIN_BITS		((uint8_t)0x07)
#define SUB_HW_GAIN				0
#define SUB_HW_GAIN_BITS		((uint8_t)0x0f)
#define SUB_24BIT_OUT			6
#define SUB_24BIT_OUT_BITS		((uint8_t)0x01)
#define SUB_POSTSHIFT			3
#define SUB_POSTSHIFT_BITS		((uint8_t)0x07)
#define SUB_THRESH_EN			0
#define SUB_THRESH_EN_BITS		((uint8_t)0x03)
#define SUB_COUNTER_INDEX		6
#define SUB_COUNTER_INDEX_BITS	((uint8_t)0x03)

// adc mux settings
#define ADCM_SMALL_IR			((uint8_t)0x00)
#define ADCM_MEDIUM_IR			((uint8_t)0x01)
#define ADCM_LARGE_IR			((uint8_t)0x02)
#define ADCM_WHITE				((uint8_t)0x0b)
#define ADCM_LARGE_WHITE		((uint8_t)0x0d)
#define ADCM_UV					((uint8_t)0x18)
#define ADCM_UV_DEEP			((uint8_t)0x19)

// sw gain settings
#define SWGAIN_1				1
#define SWGAIN_2				2
#define SWGAIN_4				3
#define SWGAIN_8				4
#define SWGAIN_16				5
#define SWGAIN_32				6
#define SWGAIN_128				7


#endif