#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c.h"

#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#define I2C_PORT_NUMBER 1

#define I2C_MASTER_SCL_IO 32              			/*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 33               			/*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUMBER(1) 				/*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000        			/*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */

i2c_port_t i2c_master_port = I2C_PORT_NUMBER;

void init_i2c()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

