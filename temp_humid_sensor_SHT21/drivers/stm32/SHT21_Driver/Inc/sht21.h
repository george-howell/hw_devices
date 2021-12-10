/*
 *
 */

#ifndef _SHT21_H_
#define _SHT21_H_

/*
 * Macros
 */

// I2C Device Address
#define SHT21_DEV_ADDR						0x80 // 7-bit I2C device address

// Commands
#define SHT21_TRIG_T_MEAS_HM                0xE3
#define SHT21_TRIG_RH_MEAS_HM               0xE5
#define SHT21_TRIG_T_MEAS_NHM               0xF3
#define SHT21_TRIG_RH_MEAS_NHM              0xF5
#define SHT21_WRITE_USER_REG                0xE6
#define SHT21_READ_USER_REG                 0xE7
#define SHT21_SW_RST                        0xFE

// User Reg Read
#define SHT21_UREG_ALL                      0xC7
#define SHT21_UREG_MEASRES                  0x81
#define SHT21_UREG_HEATER                   0x04
#define SHT21_UREG_OTPRELOAD                0x02

// User Register Write
#define SHT21_UREG_MEASRES_RH12_T14         0x00
#define SHT21_UREG_MEASRES_RH8_T12          0x01
#define SHT21_UREG_MEASRES_RH10_T13         0x80
#define SHT21_UREG_MEASRES_RH11_T11         0x81

#define SHT21_UREG_HEATER_DI                0x00
#define SHT21_UREG_HEATER_EN                0x04

#define SHT21_UREG_OTPRELOAD_EN             0x00
#define SHT21_UREG_OTPRELOAD_DI             0x02

#endif /* _SHT21_DRIVER_H_ */
