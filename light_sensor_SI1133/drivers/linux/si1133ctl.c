#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "millisleep.h"
#include "i2c.h"
#include "si1133.h"
#include <string.h>

// read an i2c subaddress
uint8_t rdSubAddr(uint8_t subAddr)
{
	// create command byte
	uint8_t cmdByte = PARAM_QUERY | subAddr;

	// write to command reg
	i2cEnWrByte(MAIN_CMD, cmdByte);

	// check cmdErr for error
	uint8_t rdData = i2cEnRdByte(MAIN_RESP0);
	if ((rdData>>MAIN_CMD_ERR) & MAIN_CMD_ERR)
	{
		printf("ERROR: could not read from subaddress 0x%.2x\n", subAddr);
		exit(EXIT_FAILURE);
	}

	// read response1 to get read data
	rdData = i2cEnRdByte(MAIN_RESP1);

	return rdData;
}

// write to an i2c subaddress
void wrSubAddr(uint8_t subAddr, uint8_t wrData)
{
	// write to input0
	i2cEnWrByte(MAIN_INPUT0, wrData);

	// create command byte
	uint8_t cmdByte = PARAM_SET | subAddr;

	// write to command reg
	i2cEnWrByte(MAIN_CMD, cmdByte);

	// check cmdErr for error
	uint8_t rdData = i2cEnRdByte(MAIN_RESP0);
	if ((rdData>>MAIN_CMD_ERR) & MAIN_CMD_ERR)
	{
		printf("ERROR: could not write 0x%.2x to subaddress 0x%.2x\n", wrData, subAddr);
		exit(EXIT_FAILURE);
	}
}

// read channel config register
void rdChConfig(void)
{	
	/* 
		ADCCONFIGx 
	*/
	uint8_t rdData = rdSubAddr(SUB_ADCCONFIG0);
	printf("ADCCONFIGx:\n");

	// DECIM_RATE
	uint8_t regBits = (rdData>>SUB_DECIM_RATE) & SUB_DECIM_RATE_BITS;
	printf("   Dec Rate: ");
	if (regBits==0)
	{
		printf("1024\n");
	} else if (regBits==1)
	{
		printf("2048\n");
	} else if (regBits==2)
	{
		printf("4096\n");
	} else
	{
		printf("512\n");
	}

	// ADCMUX
	regBits = (rdData>>SUB_ADCMUX) & SUB_ADCMUX_BITS;
	printf("   ADC Mux: ");
	if (regBits==ADCM_SMALL_IR)
	{
		printf("small ir\n");
	} else if (regBits==ADCM_MEDIUM_IR)
	{
		printf("medium ir\n");
	} else if (regBits==ADCM_LARGE_IR)
	{
		printf("large ir\n");
	} else if (regBits==ADCM_WHITE)
	{
		printf("white\n");
	} else if (regBits==ADCM_LARGE_WHITE)
	{
		printf("large white\n");
	} else if (regBits==ADCM_UV)
	{
		printf("uv\n");
	} else if (regBits==ADCM_UV_DEEP)
	{
		printf("uv-deep\n");
	} else
	{
		printf("0x%.2x\n",  regBits);
	}

	/* 
		ADCSENSx 
	*/
	printf("ADCSENSx:\n");
	rdData = rdSubAddr(SUB_ADCSENS0);


	// HSIG
	regBits = (rdData>>SUB_HSIG) & SUB_HSIG_BITS;
	printf("   HSIG: ");
	if (regBits)
	{
		printf("high gain\n");
	} else
	{
		printf("normal gain\n");
	}

	// SW_GAIN
	regBits = (rdData>>SUB_SW_GAIN) & SUB_SW_GAIN_BITS;
	printf("   SW_GAIN: %d\n", 1<<regBits);

	// HW_GAIN
	regBits = (rdData>>SUB_HW_GAIN) & SUB_HW_GAIN_BITS;
	printf("   HW_GAIN: %.1f us\n", (float)(1<<regBits) * 24.4);

	/* 
		ADCPOSTx 
	*/
	printf("ADCPOSTx:\n");
	rdData = rdSubAddr(SUB_ADCPOST0);

	// 24BIT_OUT
	regBits = (rdData>>SUB_24BIT_OUT) & SUB_24BIT_OUT_BITS;
	printf("   24BIT_OUT: ");
	if (regBits)
	{
		printf("24 bit signed int\n");
	} else
	{
		printf("16 bit unsigned int\n");
	}

	// POSTSHIFT
	printf("   POSTSHIFT: %d\n", (rdData>>SUB_POSTSHIFT) & SUB_POSTSHIFT_BITS);

	// THRESH_EN
	regBits = (rdData>>SUB_THRESH_EN) & SUB_THRESH_EN_BITS;
	printf("   THRESH_EN: ");
	if (regBits==0)
	{
		printf("Do not use THRESHOLD's\n");
	} else if (regBits==1)
	{
		printf("Interrupt when the measurement is larger than the THRESHOLD0 Global Parameters\n");
	} else if (regBits==2)
	{
		printf("Interrupt when the measurement is larger than the THRESHOLD1 Global Parameters\n");
	} else if (regBits==3)
	{
		printf("Interrupt when the measurement is larger than the THRESHOLD2 Global Parameters\n");
	}

	/* 
		MEASCONFIGx 
	*/
	printf("MEASCONFIGx:\n");
	rdData = rdSubAddr(SUB_MEASCONFIG0);

	regBits = (rdData>>SUB_COUNTER_INDEX) & SUB_COUNTER_INDEX_BITS;
	printf("   COUNTER_INDEX: ");
	if (regBits==0)
	{
		printf("No counter selected\n");
	} else
	{
		printf("MEASCOUNT%d\n", regBits);
	}
}


void setupSensor(void)
{

	/* 
		ADCCONFIG0 
	*/

	// set adc mux
	uint8_t rdData = rdSubAddr(SUB_ADCCONFIG0);
	rdData &= ~(SUB_ADCMUX_BITS << SUB_ADCMUX);
	rdData |= (ADCM_WHITE << SUB_ADCMUX);
	wrSubAddr(SUB_ADCCONFIG0, rdData);

	/*
		ADCSENS0
	*/

	// set sw gain
	rdData = rdSubAddr(SUB_ADCSENS0);
	rdData &= ~(SUB_SW_GAIN_BITS << SUB_SW_GAIN);
	rdData |= (SWGAIN_32 << SUB_SW_GAIN);
	wrSubAddr(SUB_ADCSENS0, rdData);

	/*
		ADCPOST0
	*/


	/*
		MEASCONFIG0
	*/

	/*
		CHAN_LIST
	*/
	wrSubAddr(SUB_CHAN_LIST, 0x01);
	rdData = rdSubAddr(SUB_CHAN_LIST);

}

uint16_t rdSensor(void)
{
	// force sensor to taking a reading
	i2cEnWrByte(MAIN_CMD, FORCE);

	// pause to let sensor capture measurement
	sleepMillisec(0, 100);

	// read HOSTOUT0 for msb byte
	uint8_t rdData = i2cEnRdByte(MAIN_HOSTOUT0);
	uint16_t totData = (rdData << 8);

	// read HOSTOUT1 for lsb byte
	rdData = i2cEnRdByte(MAIN_HOSTOUT1);
	totData |= rdData;

	return totData;
}

void usage(void)
{
	printf("SI1133CTL Usage:\n");
	printf("   chCfg - read channel 0 config\n");
	printf("   read - read sensor\n");

	exit(EXIT_FAILURE);
}

int main (int argc, char** argv)
{
	// parse input arguments
	if (argc!=2)
	{	
		printf("Usage Error\n");
		usage();
	}

	// open i2c on bus 1 and set device address to 0x55
	i2cOpen(1);
	i2cInit(0x55);

	if (!strcmp(argv[1], "chCfg"))
	{
		rdChConfig();
	} else if (!strcmp(argv[1], "read"))
	{
		// setup sensor
		setupSensor();

		// read sensor
		printf("rdData: %d\n", rdSensor());
	} else
	{
		// close i2c bus
		i2cClose();

		printf("Usage Error\n");
		usage();
	}

	// close i2c bus
	i2cClose();

	return(EXIT_SUCCESS);
}