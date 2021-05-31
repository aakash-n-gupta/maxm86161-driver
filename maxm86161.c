/* Driver code for MAXM86161
Using Cortex M4 as the development platform

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
void calibrate();

int main(void)
{
}

/* 1) Write 0x00 to the following register addresses: 0x02, 0x03, 0x0D, 0x10, 0x12, 0x13, 0x20.
2) Set the PPG1_ADC_RGE and PPG_TINT bit fields in the PPG_Configuration1 register 0x11 to the values required for the intended application.
3) Set the START_CAL bit to one on the DAC Calibra-tion Enable register 0x50.
4) Wait for 200ms for the self-calibration procedure to complete.
5) Monitor the CAL_DAC_Complete bit in the DAC Calibration Enable register to go high, indicating the calibration procedure is complete.
6) Check the CAL_DAC1_OOR and bits in the DAC Calibration Enable register to verify that self-calibration has completed successfully.
7) Configure the registers 0x02, 0x03, 0x0D, 0x10, 0x12, and 0x13 in any order for the application intended.
8) Finally, write register 0x20 to start the MAXM86161 measurement sequence */
void calibrate()
{
}