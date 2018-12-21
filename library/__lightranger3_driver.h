/*
    __lightranger3_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __lightranger3_driver.h
@brief    LightRanger_3 Driver
@mainpage LightRanger_3 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   LIGHTRANGER3
@brief      LightRanger_3 Click Driver
@{

| Global Library Prefix | **LIGHTRANGER3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **apr 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _LIGHTRANGER3_H_
#define _LIGHTRANGER3_H_

/** 
 * @macro T_LIGHTRANGER3_P
 * @brief Driver Abstract type 
 */
#define T_LIGHTRANGER3_P    const uint8_t*

/** @defgroup LIGHTRANGER3_COMPILE Compilation Config */              /** @{ */

//  #define   __LIGHTRANGER3_DRV_SPI__                            /**<     @macro __LIGHTRANGER3_DRV_SPI__  @brief SPI driver selector */
   #define   __LIGHTRANGER3_DRV_I2C__                            /**<     @macro __LIGHTRANGER3_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __LIGHTRANGER3_DRV_UART__                           /**<     @macro __LIGHTRANGER3_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup LIGHTRANGER3_VAR Variables */                           /** @{ */

// Registers
extern const uint8_t _LIGHTRANGER3_REG_ICSR;
extern const uint8_t _LIGHTRANGER3_REG_IER;
extern const uint8_t _LIGHTRANGER3_REG_CMD;
extern const uint8_t _LIGHTRANGER3_REG_DEV_STATUS;
extern const uint8_t _LIGHTRANGER3_REG_RESULT;
extern const uint8_t _LIGHTRANGER3_REG_RESULT_CONFIG;
extern const uint8_t _LIGHTRANGER3_REG_CMD_CONFIG_A;
extern const uint8_t _LIGHTRANGER3_REG_CMD_CONFIG_B;
extern const uint8_t _LIGHTRANGER3_REG_HOST_TO_MCPU_MBX;
extern const uint8_t _LIGHTRANGER3_REG_MCPU_TO_HOST_MBX;
extern const uint8_t _LIGHTRANGER3_REG_PMU_CONFIG;
extern const uint8_t _LIGHTRANGER3_REG_I2C_ADDR_PTR;
extern const uint8_t _LIGHTRANGER3_REG_I2C_DATA_PTR;
extern const uint8_t _LIGHTRANGER3_REG_I2C_INIT_CFG;
extern const uint8_t _LIGHTRANGER3_REG_MCPU_PM_CTRL;
extern const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_0;
extern const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_1;
extern const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_2;
extern const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_3;
extern const uint8_t _LIGHTRANGER3_REG_DEVICE_ID;
extern const uint8_t _LIGHTRANGER3_REG_PTCH_MEMORY_CFG;

extern const uint8_t _LIGHTRANGER3_STANDBY_MODE;
extern const uint8_t _LIGHTRANGER3_OFF_MODE;
extern const uint8_t _LIGHTRANGER3_ON_MODE;
extern const uint8_t _LIGHTRANGER3_MEASUREMENT_MODE;

                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup LIGHTRANGER3_INIT Driver Initialization */              /** @{ */

#ifdef   __LIGHTRANGER3_DRV_SPI__
void lightranger3_spiDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P spiObj);
#endif
#ifdef   __LIGHTRANGER3_DRV_I2C__
void lightranger3_i2cDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P i2cObj, uint8_t slave);
#endif
#ifdef   __LIGHTRANGER3_DRV_UART__
void lightranger3_uartDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup LIGHTRANGER3_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions for write one byte in register
 *
 * @param[in] reg    Register in which the data will be written
 * @param[in] _data  Data which be written in the register
 *
 * Use this function when you need to written one byte into the register
 */
void lightranger3_writeByte(uint8_t reg, uint8_t _data);

/**
 * @brief Functions for write data in register
 *
 * @param[in] reg    Register in which the data will be written
 * @param[in] _data  Data which be written in the register
 *
 * Use this function when you need to written data into the register
 */
void lightranger3_writeData(uint8_t reg, uint16_t _data);

/**
 * @brief Functions for read one byte from register
 *
 * @retval one byte data which is read from the register
 *
 * Use this function when you need to reads one byte from the register
 */
uint8_t lightranger3_readByte(uint8_t reg);

/**
 * @brief Functions for read data from register
 *
 * @retval two byte data which is read from the register
 *
 * Use this function when you need to reads data from the register
 */
uint16_t lightranger3_readData(uint8_t reg);

/**
 * @brief Functions for initializes chip
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the init failed, 
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 * Procedure for init:
      - Go to standby mode
      - Check standby status
      - Driver INT_PAD high init
      - Consfigure I2C interface
      - Set Initialization
      - Go to off mode
      - Check MCPU off status
      - Set Initialization
      - Go to on mode
      - Check MCPU on status
      - ToF configuration
 *
 * note : Procedure has been written following instructions from the datasheet.
 *
 */
uint8_t lightranger3_init();

/**
 * @brief Functions for go to standby mode
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the chip failed to go to standby mode
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 */
uint8_t lightranger3_setStandbyMode();

/**
 * @brief Functions for go to offMode
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the chip failed to go to offMode
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 */
uint8_t lightranger3_setOffMode();

/**
 * @brief Functions for go to onMode
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the chip failed to go to onMode
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 */
uint8_t lightranger3_setOnMode();

/**
 * @brief Functions for go to measurement mode
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the chip failed to go to measurement mode
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 */
uint8_t lightranger3_setMeasurementMode();

/**
 * @brief Functions for measurement
 *
 * @retval returns an error message "LIGHTRANGER3_ERROR" if the chip failed start measuremen
           else returns a message "LIGHTRANGER3_OK" about the successfully executed function.
 *
 * This function must be called in to start measuring.
 */
uint8_t lightranger3_takeSingleMeasurement();

/**
 * @brief Functions for reads distance
 *
 * @retval Distance which reads from the sensor.
 */
uint16_t lightranger3_getDistance();

/**
 * @brief Functions for reads confidence value
 *
 * @retval confidence value which reads from the sensor
 */
uint16_t lightranger3_getConfidenceValue();

/**
 * @brief Functions for reads device ID
 *
 * @retval  device ID which reads from the register.
 */
uint16_t lightranger3_getDeviceID();

/**
 * @brief Functions for softReset
 */
void lightranger3_softReset();

/**
 * @brief Functions for reads interrupt pin
 *
 * @retval status reading from pins
 */
uint8_t lightranger3_getInterrupt();







                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_LightRanger_3_STM.c
    @example Click_LightRanger_3_TIVA.c
    @example Click_LightRanger_3_CEC.c
    @example Click_LightRanger_3_KINETIS.c
    @example Click_LightRanger_3_MSP.c
    @example Click_LightRanger_3_PIC.c
    @example Click_LightRanger_3_PIC32.c
    @example Click_LightRanger_3_DSPIC.c
    @example Click_LightRanger_3_AVR.c
    @example Click_LightRanger_3_FT90x.c
    @example Click_LightRanger_3_STM.mbas
    @example Click_LightRanger_3_TIVA.mbas
    @example Click_LightRanger_3_CEC.mbas
    @example Click_LightRanger_3_KINETIS.mbas
    @example Click_LightRanger_3_MSP.mbas
    @example Click_LightRanger_3_PIC.mbas
    @example Click_LightRanger_3_PIC32.mbas
    @example Click_LightRanger_3_DSPIC.mbas
    @example Click_LightRanger_3_AVR.mbas
    @example Click_LightRanger_3_FT90x.mbas
    @example Click_LightRanger_3_STM.mpas
    @example Click_LightRanger_3_TIVA.mpas
    @example Click_LightRanger_3_CEC.mpas
    @example Click_LightRanger_3_KINETIS.mpas
    @example Click_LightRanger_3_MSP.mpas
    @example Click_LightRanger_3_PIC.mpas
    @example Click_LightRanger_3_PIC32.mpas
    @example Click_LightRanger_3_DSPIC.mpas
    @example Click_LightRanger_3_AVR.mpas
    @example Click_LightRanger_3_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __lightranger3_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */