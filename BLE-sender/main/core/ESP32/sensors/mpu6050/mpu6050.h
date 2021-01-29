#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <stdbool.h>

#define TICK_DELAY 10

#define I2C_PORT_NUMBER 1

#define MPU6050_SENSOR_ADDR	0x68	/*Device Address/Identifier for MPU6050*/
#define WRITE_BIT 			I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT 			I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 		0x1                        /*!< I2C master will check ack from slave*/

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47
#define MPU_ID       0x75

int8_t slave_read_byte(uint8_t);
bool slave_write_byte(uint8_t, uint8_t); 
bool check_mpu6050(void);
void init_mpu6050(bool);
void print_mpu6050(void);
char* get_mpu6050(int);

#endif
