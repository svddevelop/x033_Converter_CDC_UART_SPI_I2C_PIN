# USB programmable converter based on CH32X033

Using CDC (USB) connection you can

programmatically control interfaces

![<img src="img/cfg-CDC_UART_SPI_I2C_Convertor3_top.JPG" width="100"](img/CDC_UART_SPI_I2C_Convertor3_top.JPG)	![<img src="img/cfg-CDC_UART_SPI_I2C_Convertor3_bottom.JPG" width="100">](img/CDC_UART_SPI_I2C_Convertor3_bottom.JPG)	


## Current commands
When the device is connected via USB, by connecting a terminal, you can get help on using the control commands. At the end of each command there must be a CR (0x0D) symbol.

### [help]
outputs information about possible commands.

### [print]
outputs the current configuration settings

### [helpuart]
commands for configuring the UART interface:

### [helpspi]
shows list of commands for configuring the SPI interface:

### [helpi2c]
shows list of commands for configuring the UART interface:

### [SAVE]

saves the current setting to the flash. On the next powrt connection of the device, this configuration will be automatic activated.

#### [SET:UART.DIS]
makes the UART interface unused.

##### [SET:UART.DIS]
activates the UART interface.

#### [SET:UART.BAUD=\<int value>]
Sets the communication speed for the UART interface. <int value> must be a value from 1200 to 2500000 baud per second.

Example: [SET:UART.BAUD=57600] - sets the communication speed to 57600.

### [SET:SPI.PRESC=\<char value>]
set the base clock prescaler:

BASE CLOCK = 48MHz /(2 << PRESC );

### [SET:SPI.BAUD=\<char value>]
makes division of base clock (see PRESC) with value:

  0	divede by 2,  
  1	divide by 4,  
  2	divide by 8,  
  3	divide by 16,  
  4	divide by 32,  
  5	divide by 54,  
  6	divide by 128,  
  7	divide by 256.  

#### [SET:SPI.DIS]
makes the SPI interface unused.

#### [SET:SPI.DIS]
activates the SPI interface.

#### [SET:SPI.CPOL=\<char val>]
set up the clock polarity (0 or 1); 

#### [SET:SPI.CPHA=\<char val>]
set up the clock phase (0 or 1); 

#### [TRN:\<dev src>-\<dev dst>.EN/DIS]
allow or disallow to transwer between interfaces where <dev src> and <dev dst> is:

  CDC, UART, SPI or I2C;
		
for example:

  [TRN:CDS-UART.EN] - allow a trafik from CDS to UART.
	
  [TRN:UART-UART.EN] - allow a trafik from UART to CDS.

---

![<img src="img/cfg-help.JPG" width="100">](img/cfg-help.JPG) ![<img src="img/cfg-helpuart.JPG" width="100">](img/cfg-helpuart.JPG)
![<img src="img/cfg-helpi2c.JPG" width="100">](img/cfg-helpi2c.JPG)
![<img src="img/cfg-helpspi.JPG" width="100">](img/cfg-helpspi.JPG) ![<img src="img/cfg-uartbaud-save.JPG" width="100">](img/cfg-uartbaud-save.JPG)





