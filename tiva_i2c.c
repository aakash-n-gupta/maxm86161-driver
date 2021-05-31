#include "../TexasInstruments/tm4c123gh6pm.h"

void init_i2c_master();
void set_slave_addr(int, int);
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

// sets the slave adderss in the i2c_Master slacae adderss, along with read write bit
void set_slave_addr(int address, int RW)
{
    // adderss is 7 bits, 8th bit is the R/W bit
    // bit shifting and updating the address with R/W bit
    address = address << 1 + RW;
}

void i2c0_send_data(int data, int slave_addr_r)
{
    // 6th bit is busbusy, 0 means idle

    // for MAXM86161, 3 bytes of data must be transmitted, slave_addr,
    // slave_arre_reg - where the data will be written to in the IC and the data itself
    while ((I2C0_MCS_R & 0x00000040) == 0)
    {
        // first slave address reg is transmitted
        I2C0_MDR_R = slave_addr_r;

        // after this, data is transmitted
        I2C0_MDR_R = data;
    }

    // maybe some offset is needed to write data to specific location to the slave device??
}

int i2c0_recieve_data(int slave_addr)
{
}
