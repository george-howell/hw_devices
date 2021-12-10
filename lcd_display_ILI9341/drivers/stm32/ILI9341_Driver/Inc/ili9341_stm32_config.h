/*
 * ili9341_stm32_config.h
 *
 * Configuration for the ILI93241 LCD Display.
 *
 *  Created on: Nov 4, 2021
 *      Author: George.Howell
 */

#ifndef ILI9341_STM32_CONFIG_H
#define ILI9341_STM32_CONFIG_H

// STM32 device header (select appropriate file)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"

// SPI Instance Handle
#define HSPI_INSTANCE							&hspi1

// SPI Chip Select GPIO Port and Pin [Standard GPIO Output]
#define LCD_CS_PORT								GPIOB
#define LCD_CS_PIN								GPIO_PIN_5

// Data Command GPIO Port and Pin [Standard GPIO Output]
#define LCD_DC_PORT								GPIOB
#define LCD_DC_PIN								GPIO_PIN_3

// Reset GPIO Port and Pin [Standard GPIO Output]
#define	LCD_RST_PORT							GPIOA
#define	LCD_RST_PIN								GPIO_PIN_1

#endif /* ILI9341_STM32_CONFIG_H */
