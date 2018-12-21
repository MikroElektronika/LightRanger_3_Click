/*
Example for LightRanger_3 Click

    Date          : apr 2018.
    Author        : Katarina Perendic

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.2.1.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as INPUT
- Application Initialization - Initializes driver init and configuration chip
- Application Task - (code snippet) - Includes measurements, reads distance, and logs distance to USBUART for every 300 ms.
                                      Distance measurement at distances ranging from 100 mm to 2000 mm

*/

#include "Click_LightRanger_3_types.h"
#include "Click_LightRanger_3_config.h"

uint16_t Distance;
char DistanceTxt[20] = { 0 };

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_i2cInit( _MIKROBUS1, &_LIGHTRANGER3_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART, 9600 );

    mikrobus_logWrite( " --- System Init --- ", _LOG_LINE );
    Delay_ms( 100 );
}

void applicationInit()
{
    lightranger3_i2cDriverInit( (T_LIGHTRANGER3_P)&_MIKROBUS1_GPIO, (T_LIGHTRANGER3_P)&_MIKROBUS1_I2C, 0x4C );
    if(lightranger3_init() == 0)
    {
        mikrobus_logWrite( " --- Device init successfully --- ", _LOG_LINE );
    }
    else
    {
       mikrobus_logWrite( " ---  Device init error --- ", _LOG_LINE );
    }
}

void applicationTask()
{
      lightranger3_takeSingleMeasurement();

      Distance = lightranger3_getDistance();
      IntToStr(Distance,DistanceTxt);
      mikrobus_logWrite( "Distance =", _LOG_TEXT );
      mikrobus_logWrite( DistanceTxt, _LOG_TEXT );
      mikrobus_logWrite( " mm", _LOG_LINE );
      Delay_ms( 300 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}