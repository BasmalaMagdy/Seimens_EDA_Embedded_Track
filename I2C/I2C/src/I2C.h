/*
 * I2C.h
 *
 *  Created on: Aug 28, 2021
 *  Author: Basmala Magdy
 */

/***************************************
********* INCLUDES ************
****************************************/

#include "tm4c123gh6pm.h"
#include "platform_types.h"
#include <stdint.h>

/***************************************
********* PUBLIC DEFENTIONS ************
****************************************/


/* 4 I2C modules */


/*clock enable */
#define I2C0_CE 0x01       /* PB2 -> SCL    PB3 -> SDA */
#define I2C1_CE 0x02       /* PA6 -> SCL    PA7 -> SDA */
#define I2C2_CE 0x04       /* PB4 -> SCL    PB5 -> SDA */
#define I2C3_CE 0x08       /* PD0 -> SCL    PD1 -> SDA */


//clock speed
/*the eq of clock speed is
TPR = (sys_clk_freq)/(20*i2c_clk)-1
 we have 4 i2c_clk speed {100 kbps,400 kbps,1 Mbps,3.3 Mbps}
so you can claculate the tpr value
*/
#define SYS_CLK_FRE 16000000
#define I2C_CLK     100000
#define TPR    (SYS_CLK_FRE)/(20*I2C_CLK)-1

//i2c mode
#define MASTER    0x10
#define SLAVE     0x20



/***************************************
************* PUBLIC FUNCTIONS *********
****************************************/


void I2C_init(int8_t I2C_NUM ,uint8_t I2C_MODE);

static int8_t I2C_wait_till_done(int8_t I2C_NUM);

uint8_t I2C_byteWrite(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t data);

uint8_t I2C_byteread(int8_t I2C_NUM ,int8_t slaveAddr, int8_t memAddr, uint8_t* data);

uint8_t I2C_burstWrite(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data);

uint8_t I2C_burstread(int8_t I2C_NUM,int8_t slaveAddr, int8_t memAddr, int8_t byteCount, uint8_t* data);
