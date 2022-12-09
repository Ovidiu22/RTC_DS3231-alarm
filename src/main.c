/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	09th November 2022	 ***/
/*******************************/

#include <asf.h>
#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_basic.h"
#include "I2C.h"
#include "LCD.h"

int main (void)
{
	ds3231_time_t t;
	ds3231_basic_init();
	initLCD();

	
	i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_CONTROL);
	i2c_write(0x1);

	i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_STATUS);
	i2c_write(0x0);
	
	/* Read and display current time */
	while(1)
	{
		i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_STATUS);
		/* Send START condition with SLA+R */
		i2c_rep_start((DS3231_ADDRESS<<1)+I2C_READ);
		/* Receive data */
		uint8_t st_reg = i2c_readNak();
		
		
		i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_CONTROL);
		/* Send START condition with SLA+R */
		i2c_rep_start((DS3231_ADDRESS<<1)+I2C_READ);
		/* Receive data */
		uint8_t ctrl_reg = i2c_readNak();
		
		ds3231_basic_get_time(&t);
		displayLCD_main(1, "Status reg: ", st_reg, "NONE");
		displayLCD_main(2, "Control reg: ", ctrl_reg, "NONE");
	
		displayLCD_main(3, "Minute:", t.minute, "NONE");
		displayLCD_main(4, "Second:", t.second, "NONE");
	}
	return 0;
}
