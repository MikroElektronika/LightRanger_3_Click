![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# LightRanger_3 Click

- **CIC Prefix**  : LIGHTRANGER3
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : apr 2018.

---

### Software Support

We provide a library for the LightRanger_3 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2398/lightranger-3-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for writing data in registers and reading data
from registers. 
The library includes functions for full initialization chip with procedure is written following the instructions from the datasheet.
The user has the functions available for softReset, read distance and confidence distance value,
Then functions for go to standby mode, go to off mode, go to on mode and measurement mode.

Key functions :

- ``` uint8_t lightranger3_init() ``` - Functions for initializes chip
- ``` uint8_t lightranger3_takeSingleMeasurement() ``` - Functions for measurement
- ``` uint16_t lightranger3_getDistance() ``` - Functions for reads distance

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as INPUT
- Application Initialization - Initializes driver init and configuration chip
- Application Task - (code snippet) - Includes measurements, reads distance, and logs distance to USBUART for every 300 ms.
                                      Distance measurement at distances ranging from 100 mm to 2000 mm

```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2398/lightranger-3-click) page.

Other mikroE Libraries used in the example:

- Configuration
- I2C
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
