#ifndef _BH1750_H_
#define _BH1750_H_

#include <stdbool.h>

#define TICK_DELAY 10

#define I2C_PORT_NUMBER 1

#define BH1750_SENSOR_ADDR 0x23   /*!< slave address for BH1750 sensor */
#define BH1750_CMD_START 0x23   /*!< Operation mode */
#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

bool check_bh1750(void);
void init_bh1750(bool);
char* get_bh1750(void);
void print_bh1750(void);

#endif
