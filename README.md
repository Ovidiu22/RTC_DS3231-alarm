# RTC_DS3231-alarm
 
A project for setting an alarm using the DS3231 module and then reading the time and alarm flag using an Arduino.
- Reading time is done using the driver from LibDriver https://www.libdriver.com/docs/ds3231/index.html
- Time is displayed on a 20x4 LCD
- After alarm is triggered, alarm flag is cleared for the next cycle
- Communication between Arduino and RTC module DS3231 is done over I2C

# Schematic![Schematic](https://user-images.githubusercontent.com/75970114/206840080-4690fa39-e43d-443c-b148-3235da640406.png)
