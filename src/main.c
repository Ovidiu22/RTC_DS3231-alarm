/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	10th December 2022	 ***/
/*******************************/

#include <asf.h>
#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_basic.h"
#include "I2C.h"
#include "LCD.h"

uint8_t dec2bcd(uint8_t);

int main (void)
{
	ds3231_time_t t;
	
	initLCD();
	ds3231_basic_init();

	/* Set alarm */
	i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_SECOND);
	i2c_write(dec2bcd(33));	// Seconds in dec
	
	i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_CONTROL);
	i2c_write(0x5);		// Set bit 0 and 2 (alarm 1 and interrupt)

	/* Read and display current time */
	while(1)
	{
		i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_STATUS);
		/* Send START condition with SLA+R */
		i2c_rep_start((DS3231_ADDRESS<<1)+I2C_READ);
		/* Receive data */
		uint8_t st_reg = i2c_readNak();
		
		ds3231_basic_get_time(&t);
		displayLCD_main(1, "Alarm flag: ", (st_reg & 0x01), "NONE");
		displayLCD_main(2, "Hour: ", t.hour, "NONE");
		displayLCD_main(3, "Minutes:", t.minute, "NONE");
		displayLCD_main(4, "Second:", t.second, "NONE");
		
		if ((st_reg & 0x01) > 0)
		{
			_delay_ms(200);
			i2c_start((DS3231_ADDRESS<<1)+I2C_WRITE);
			i2c_write(DS3231_REG_STATUS);
			i2c_write(0x0);
		}
	}
	return 0;
}

/* *****************************************************************
Name:		dec2bcd()
Inputs:		Value to be converted for DS3231 registers
Outputs:	Value for seconds, minutes, hour registers
Description:converts decimal values into ds3231 register format
******************************************************************** */
uint8_t dec2bcd(uint8_t val)
{
	uint8_t i, j, k;
	
	i = val / 10;            /* get tens place */
	j = val % 10;            /* get ones place */
	k = j + (i << 4);        /* set bcd */
	
	return k;                /* return bcd */
}