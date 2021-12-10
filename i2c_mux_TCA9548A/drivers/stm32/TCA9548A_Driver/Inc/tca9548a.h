/*
 *  tca9548a.h
 *
 *  A basic library for the TI TCA9548a I2C mux.
 *
 *  Created on: Dec 9, 2021
 *  Author: George.Howell
 */

#ifndef _TCA9548A_H_
#define _TCA9548A_H_

/*
 * Macros
 */

#define TCA9548A_DEV_ADDR                   ((uint8_t)0xE0)
#define TCA9548A_I2C_TIMEOUT                ((uint8_t)0xFF)

#define TCA9548A_PORT_0                     ((uint8_t)0x00)
#define TCA9548A_PORT_1                     ((uint8_t)0x01)
#define TCA9548A_PORT_2                     ((uint8_t)0x02)
#define TCA9548A_PORT_3                     ((uint8_t)0x03)
#define TCA9548A_PORT_4                     ((uint8_t)0x04)
#define TCA9548A_PORT_5                     ((uint8_t)0x05)
#define TCA9548A_PORT_6                     ((uint8_t)0x06)
#define TCA9548A_PORT_7                     ((uint8_t)0x07)

#endif /* _TCA9548A_H_ */
