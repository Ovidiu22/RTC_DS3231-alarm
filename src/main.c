/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	09th November 2022	 ***/
/*******************************/

#include <asf.h>
#include "driver_ds3231_interface.h"
#include "driver_ds3231.h"
#include "driver_ds3231_alarm.h"
#include "I2C.h"
#include "LCD.h"

#define ALARM 0

int main (void)
{
	initLCD();

	uint8_t res;
	ds3231_time_t time;
	ds3231_alarm1_mode_t mode;
/*
	void alarm_receive_callback(uint8_t type)
	{
		switch (type)
		{
			case DS3231_STATUS_ALARM_2 :
			{
				ds3231_alarm_clear_flag(DS3231_ALARM_2);
			
				break;
			}
			case DS3231_STATUS_ALARM_1 :
			{
				ds3231_alarm_clear_flag(DS3231_ALARM_1);
			
				break;
			}
			default :
			{
			
				break;
			}
		}
	}


	res = ds3231_alarm_init(alarm_receive_callback);
	if (res != 0)
	{
		return 1;
	}
*/

// 	res = gpio_interrupt_init();
// 	if (res != 0)
// 	{
// 		(void)ds3231_alarm_deinit();
// 
// 		return 1;
// 	}


// 	mode = DS3231_ALARM1_MODE_ONCE_A_SECOND;
// 	time.am_pm = DS3231_AM;
// 	time.date = 01;
// 	time.format = DS3231_FORMAT_24H;
// 	time.hour = 7;
// 	time.minute = 00;
// 	time.month = 0;
// 	time.second = 00;
// 	time.week  = 1;
// 	time.year = 0;
// 	res = ds3231_alarm_set_alarm1(&time, mode);
	
// 	if (res != 0)
// 	{
// 		(void)ds3231_alarm_deinit();
// 
// 		return 1;
// 	}
// 
// 
// 	res = ds3231_alarm_enable(DS3231_ALARM_1);
// 	if (res != 0)
// 	{
// 		(void)ds3231_alarm_deinit();
// 
// 		return 1;
// 	}

	


#if ALARM
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_CONTROL);
	i2c_write(0x5);

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_SECOND);
	i2c_write(20);

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_MINUTE);
	i2c_write(128);
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_HOUR);
	i2c_write(128);
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_WEEK);
	i2c_write(128);
#endif

#if ALARM	
	/* Receive data */
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_STATUS);
	/* Send START condition with SLA+R */
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	/* Receive data */
	uint8_t st_reg = i2c_readNak();
	if (st_reg & 0x01)
	{
		uint8_t temp_st_reg = st_reg & 0xFE;
		i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
		i2c_write(DS3231_REG_STATUS);
		i2c_write(temp_st_reg);
	}
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_CONTROL);
	/* Send START condition with SLA+R */
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	/* Receive data */
	uint8_t ctrl_reg = i2c_readNak();
	displayLCD_main(1, "Ctrl register: ", ctrl_reg, "NONE");
		
#endif

#if 0
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_SECOND);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M1 = i2c_readNak();

	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_MINUTE);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M2 = i2c_readNak();
	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_HOUR);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M3 = i2c_readNak();
	
	i2c_start((I2C_DEVICE<<1)+I2C_WRITE);
	i2c_write(DS3231_REG_ALARM1_WEEK);
	i2c_rep_start((I2C_DEVICE<<1)+I2C_READ);
	uint8_t A1M4 = i2c_readNak();
	
	displayLCD_main(1, "A1M1: ", A1M1, "NONE");
	displayLCD_main(2, "A1M2: ", A1M2, "NONE");
	displayLCD_main(3, "A1M3: ", A1M3, "NONE");
	displayLCD_main(4, "A1M4: ", A1M4, "NONE");
#endif
}
