/*
 * 	ili9341_stm32_driver.h
 *
 * 	A basic library that for the ILI9341 LCD Display that does not require either
 * 	interrupts or DMA. Adapted from the library by Matej Artnak to work with in a
 * 	CubeIDE environment.
 *
 *  Created on: Nov 4, 2021
 *  Author: George.Howell
 */

#ifndef ILI9341_STM32_DRIVER_H
#define ILI9341_STM32_DRIVER_H

#include "ili9341_stm32_config.h"
#include "ili9341_stm32_gfx.h"
#include "main.h"

/*
 * DEFINITIONS
 */

#define ILI9341_SCREEN_HEIGHT 					240
#define ILI9341_SCREEN_WIDTH 					320

#define BURST_MAX_SIZE 	500

// Colours
#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

// Rotation
#define SCREEN_VERTICAL_1			0
#define SCREEN_HORIZONTAL_1			1
#define SCREEN_VERTICAL_2			2
#define SCREEN_HORIZONTAL_2			3

/*
 * API's
 */

void ILI9341_SPI_Init(void);
void ILI9341_SPI_Send(unsigned char SPI_Data);
void ILI9341_Write_Command(uint8_t Command);
void ILI9341_Write_Data(uint8_t Data);
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void ILI9341_Reset(void);
void ILI9341_Set_Rotation(uint8_t Rotation);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_Fill_Screen(uint16_t Colour);
void ILI9341_Draw_Colour(uint16_t Colour);
void ILI9341_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour);
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
void ILI9341_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour);
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour);

#endif /* ILI9341_STM32_DRIVER_H */
