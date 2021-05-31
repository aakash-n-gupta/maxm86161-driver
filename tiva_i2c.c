#include "../TexasInstruments/tm4c123gh6pm.h"

void init_i2c_master();

// USing default I2C0 config on Port B - PB2 is clk, PB3 is data
void init_i2c_master()
{
    // enable clk for Port B
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | SYSCTL_RCGC2_GPIOB;

    // enable clock for I2C0
    SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R | SYSCTL_RCGCI2C_R0;

    // enable digital for port B - pins PB2 and PB3
    GPIO_PORTB_DEN_R = GPIO_PORTB_DEN_R | 0x0C;

    // PMC2,PMC3 for I2C0 - seen on page 688 reference
    GPIO_PORTB_AHB_PCTL_R = GPIO_PORTB_AHB_PCTL_R | 0x03;

    // Setup I2C master
    I2C0_MCR_R = 0x0010;

    // setup standard clocl speed of 100kbps
    /* 
    TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
    TPR = (20MHz/(2*(6+4)*100000))-1;
    TPR = 9
    */
    I2C0_MTPR_R = 0x09;
}