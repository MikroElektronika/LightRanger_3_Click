/*
    __lightranger3_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__lightranger3_driver.h"
#include "__lightranger3_hal.c"

/* ------------------------------------------------------------------- MACROS */

// Registers
const uint8_t _LIGHTRANGER3_REG_ICSR             = 0x00;
const uint8_t _LIGHTRANGER3_REG_IER              = 0x02;
const uint8_t _LIGHTRANGER3_REG_CMD              = 0x04;
const uint8_t _LIGHTRANGER3_REG_DEV_STATUS       = 0x06;
const uint8_t _LIGHTRANGER3_REG_RESULT           = 0x08;
const uint8_t _LIGHTRANGER3_REG_RESULT_CONFIG    = 0x0A;
const uint8_t _LIGHTRANGER3_REG_CMD_CONFIG_A     = 0x0C;
const uint8_t _LIGHTRANGER3_REG_CMD_CONFIG_B     = 0x0E;
const uint8_t _LIGHTRANGER3_REG_HOST_TO_MCPU_MBX = 0x10;
const uint8_t _LIGHTRANGER3_REG_MCPU_TO_HOST_MBX = 0x12;
const uint8_t _LIGHTRANGER3_REG_PMU_CONFIG       = 0x14;
const uint8_t _LIGHTRANGER3_REG_I2C_ADDR_PTR     = 0x18;
const uint8_t _LIGHTRANGER3_REG_I2C_DATA_PTR     = 0x1A;
const uint8_t _LIGHTRANGER3_REG_I2C_INIT_CFG     = 0x1C;
const uint8_t _LIGHTRANGER3_REG_MCPU_PM_CTRL     = 0x1E;
const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_0   = 0x20;
const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_1   = 0x22;
const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_2   = 0x24;
const uint8_t _LIGHTRANGER3_REG_HW_FW_CONFIG_3   = 0x26;
const uint8_t _LIGHTRANGER3_REG_DEVICE_ID        = 0x28;
const uint8_t _LIGHTRANGER3_REG_PTCH_MEMORY_CFG  = 0x2A;

const uint8_t _LIGHTRANGER3_STANDBY_MODE      = 0x90;
const uint8_t _LIGHTRANGER3_OFF_MODE          = 0x91;
const uint8_t _LIGHTRANGER3_ON_MODE           = 0x92;
const uint8_t _LIGHTRANGER3_MEASUREMENT_MODE  = 0x81;

static const uint8_t LIGHTRANGER3_ERROR = 0x01;
static const uint8_t LIGHTRANGER3_OK    = 0x00;
static const uint8_t DISTANCE_IS_GOOD   = 0x7FFF;



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __LIGHTRANGER3_DRV_I2C__
static uint8_t _slaveAddress;
#endif

static uint16_t _confidenceValue = 0;
static uint16_t _distance = 0;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __LIGHTRANGER3_DRV_SPI__

void lightranger3_spiDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __LIGHTRANGER3_DRV_I2C__

void lightranger3_i2cDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __LIGHTRANGER3_DRV_UART__

void lightranger3_uartDriverInit(T_LIGHTRANGER3_P gpioObj, T_LIGHTRANGER3_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

void lightranger3_writeByte(uint8_t reg, uint8_t _data)
{
    uint8_t writeReg[ 2 ];
    
    writeReg[ 0 ] = reg;
    writeReg[ 1 ] = _data;
    
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );
}

void lightranger3_writeData(uint8_t reg, uint16_t _data)
{
    uint8_t writeReg[ 3 ];

    writeReg[ 0 ] = reg;
    writeReg[ 1 ] = _data & 0x00FF; // LSB
    writeReg[ 2 ] = (_data & 0xFF00) >> 8; // MSB

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 3, END_MODE_STOP );
}

uint8_t lightranger3_readByte(uint8_t reg)
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];
    
    writeReg[ 0 ] = reg;
    
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );
    
    return readReg[ 0 ];
}

uint16_t lightranger3_readData(uint8_t reg)
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 2 ];
    uint16_t value;
    
    writeReg[ 0 ] = reg;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 2, END_MODE_STOP );

    value = readReg[ 1 ];
    value = value << 8;
    value = value | readReg[ 0 ];
    
    return value;
}

uint8_t lightranger3_init()
{
    uint8_t settings;
    
    if (lightranger3_getDeviceID() != 0xAD02 && lightranger3_getDeviceID() != 0xAD01)
    {
        return LIGHTRANGER3_ERROR;
    }
    if (lightranger3_setStandbyMode() == 1)
    { 
        return LIGHTRANGER3_ERROR;
    }
    
    lightranger3_writeData(_LIGHTRANGER3_REG_ICSR, 0x05);
    lightranger3_writeData(_LIGHTRANGER3_REG_IER, 0x01);

    lightranger3_writeData(_LIGHTRANGER3_REG_I2C_INIT_CFG, 0x65);
    lightranger3_writeData(_LIGHTRANGER3_REG_PMU_CONFIG, 0x0500);

    if (lightranger3_setOffMode() == 1)
    {
        return LIGHTRANGER3_ERROR;
    }
    
    lightranger3_writeData(_LIGHTRANGER3_REG_PMU_CONFIG, 0x0600);

    if (lightranger3_setOnMode() == 1)
    {
        return LIGHTRANGER3_ERROR;
    }

    lightranger3_writeData(_LIGHTRANGER3_REG_CMD_CONFIG_A,   0xE100);
    lightranger3_writeData(_LIGHTRANGER3_REG_CMD_CONFIG_B,   0x10FF);
    lightranger3_writeData(_LIGHTRANGER3_REG_HW_FW_CONFIG_0, 0x07D0);
    lightranger3_writeData(_LIGHTRANGER3_REG_HW_FW_CONFIG_1, 0x5008);
    lightranger3_writeData(_LIGHTRANGER3_REG_HW_FW_CONFIG_2, 0xA041);
    lightranger3_writeData(_LIGHTRANGER3_REG_HW_FW_CONFIG_3, 0x45D4);

    return LIGHTRANGER3_OK;
}

uint8_t lightranger3_setStandbyMode()
{
   uint8_t x;

   lightranger3_writeByte(_LIGHTRANGER3_REG_CMD, _LIGHTRANGER3_STANDBY_MODE);

   for (x = 0; x < 10; x++)
   {
       if ( (lightranger3_readData(_LIGHTRANGER3_REG_DEV_STATUS) & 0x001F) == 0x0000)
       {
           return LIGHTRANGER3_OK;
       }
       Delay_10us();
   }
   return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_setOffMode()
{
    uint8_t x;

    lightranger3_writeByte(_LIGHTRANGER3_REG_CMD, _LIGHTRANGER3_OFF_MODE);
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( (lightranger3_readData(_LIGHTRANGER3_REG_DEV_STATUS) & 0x001F) == 0x0010)
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us();
    }
    return LIGHTRANGER3_ERROR;
}


uint8_t lightranger3_setOnMode()
{
    uint8_t x;

    lightranger3_writeByte(_LIGHTRANGER3_REG_CMD, _LIGHTRANGER3_ON_MODE);
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( (lightranger3_readData(_LIGHTRANGER3_REG_DEV_STATUS) & 0x001F) == 0x0018)
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us();
    }
    return LIGHTRANGER3_ERROR;
}

uint8_t lightranger3_setMeasurementMode()
{
    uint8_t x;

    lightranger3_writeByte(_LIGHTRANGER3_REG_CMD, _LIGHTRANGER3_MEASUREMENT_MODE);
    for ( x = 0 ; x < 10 ; x++)
    {
        if ( (lightranger3_readByte(_LIGHTRANGER3_REG_ICSR) & (1 << 4)) != 0)
        {
            return LIGHTRANGER3_OK;
        }
        Delay_10us();
    }
    return LIGHTRANGER3_ERROR;
}


uint8_t lightranger3_takeSingleMeasurement()
{
    uint16_t readValue;
    uint8_t errorCode;
    uint16_t confidenceRegister;
    
    if (lightranger3_setMeasurementMode() == 1)
    {
        return LIGHTRANGER3_ERROR;
    }

    readValue = lightranger3_readData(_LIGHTRANGER3_REG_RESULT);

    if (readValue & DISTANCE_IS_GOOD)
    {
        errorCode = (readValue >> 13) & 0x03;
        if (errorCode == 0)
        {
            _distance = (readValue >> 2) & 0x07FF;
            
            confidenceRegister = lightranger3_readData(_LIGHTRANGER3_REG_RESULT_CONFIG);
            _confidenceValue = (confidenceRegister >> 4) & 0x07FF;
        }
        return (errorCode);
    }
    else
    {
        return LIGHTRANGER3_ERROR;
    }
}

uint16_t lightranger3_getDistance()
{
    return _distance;
}

uint16_t lightranger3_getConfidenceValue()
{
  return _confidenceValue;
}

uint16_t lightranger3_getDeviceID()
{
    return lightranger3_readData(_LIGHTRANGER3_REG_DEVICE_ID);
}

void lightranger3_softReset()
{
    lightranger3_writeByte(_LIGHTRANGER3_REG_CMD, 0x40);
    Delay_100ms();
}

uint8_t lightranger3_getInterrupt()
{
    return hal_gpio_intGet();
}




/* -------------------------------------------------------------------------- */
/*
  __lightranger3_driver.c

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