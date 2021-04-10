#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c.h"

#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"


#define I2C_PORT_NUMBER 1

#define I2C_MASTER_SCL_IO 19              			/*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 18               			/*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUMBER(0) 				/*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000        			/*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                 /*!< I2C master doesn't need buffer */

i2c_port_t i2c_master_port = I2C_PORT_NUMBER;


#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */

static const char *TAG = "cmd_i2ctools";

static gpio_num_t i2c_gpio_sda = 18;
static gpio_num_t i2c_gpio_scl = 19;
static uint32_t i2c_frequency = 100000;
static i2c_port_t i2c_port = I2C_NUM_0;


static esp_err_t i2c_master_driver_initialize(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = i2c_gpio_sda,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = i2c_gpio_scl,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = i2c_frequency,
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    return i2c_param_config(i2c_port, &conf);
}




void init_i2c()
{

    //register_system();

    i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    i2c_master_driver_initialize();
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
}

