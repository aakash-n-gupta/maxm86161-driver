/* Driver code for MAXM86161
Using Cortex M4 as the development platform
*/
#include "tiva_i2c.c"
// Register addresses for the MAXM86181
#define SYSTEM_CONTROL_R 0X0D;
#define PPG_SYNC_CTRL_R 0X10;
#define FIFO_WRITE_PTR 0X04
#define FIFO_READ_PTR 0X05
#define OVFLOW_COUNTER 0X06
#define FIFO_DATA_COUNTER 0X07
#define FIFO_DATA_REGISTER 0X08

#define FIFO_CONFIG_1 0X09
#define FIFO_CONFIG_2 0X0A
#define PPG_CONFIG_1 0X11
#define PPG_CONFIG_2 0X12
#define PPG_CONFIG_3 0X13

#define LED_SEQUENCE_R1 0X20
#define LED_SEQUENCE_R2 0X21
#define LED_SEQUENCE_R3 0X22
#define LED1_PA 0X23
#define LED2_PA 0X24
#define LED3_PA 0X25
#define LED_PILOT_PA 0X29

#define DAC_CALIBRATION_ENA 0X50

/*
Config requires I2C bus, for read write to internal FIFO

Psudocodes given
1.) Initialize Optical AFE - for spO2 application
2.) Interrupt handeling with FIFO_A_FULL
3.) Readinga data from FIFO - single photodiode channel and 2 LED channels
4.) Initialize all LEDs with direct ambient sampling - both spO2 and HR monitoring

----------------------------------------------------------------------------------------------

Required methods
1.) self_calibration() - ADC reduce sub-DAC XNL errors
2.) init_read_mode()
3.) init_write_mode()
4.) LED_config_modes() - something like that
*/

// somehow need to transmit these config functions to the sensor, before operation

void init_config()
{
    // can be configured for spO2, HRM or both simultaneously
    // green LED1 - Heartrate, red(LED2) and IR LED3 - spO2

    // config for spO2 measurement

    // LED sequence control
    i2c0_send_data(0x32, LED_SEQUENCE_R1); // ledc1 = 0x02, ledc2 = 0x03
    i2c0_send_data(0x09, LED_SEQUENCE_R2); // ledc1 = 0x02, ledc2 = 0x03
    i2c0_send_data(0x00, LED_SEQUENCE_R3); // ledc1 = 0x02, ledc2 = 0x03

    // PPG configuration
    i2c0_send_data(0x05, PPG_CONFIG_1);
    i2c0_send_data(0x05, PPG_CONFIG_2);

    // LED pulse amplitude
    i2c0_send_data(0xFE, LED2_PA); // Arbitary value selected form table @pg 55
    i2c0_send_data(0xFE, LED3_PA); // Arbitary value selected form table @pg 55
}

void config_LEDC()
{

    // some interrupt which indicates if FIFO buffer is full or about to get full
    //
}