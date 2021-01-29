#include <stdlib.h>
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "mpu6050.h"

char buffer[100];
char* s;

short value;
i2c_cmd_handle_t cmd;

bool check_mpu6050()
{
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU6050_SENSOR_ADDR << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, MPU6050_SENSOR_ADDR, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK)
    	return true;
    else
    	return false;
}

void init_mpu6050(bool _ft)
{
	slave_write_byte(SMPLRT_DIV, 0x07);
	slave_write_byte(PWR_MGMT_1, 0x01);
	slave_write_byte(CONFIG, 0);
	slave_write_byte(GYRO_CONFIG, 24);
	slave_write_byte(INT_ENABLE, 0x01);
} 

void print_mpu6050()
{
    if (check_mpu6050())
	printf("MPU6050 : OK");
    else
	printf("MPU6050 : Not detected (Accelerometer, Gyroscope sensor)");
}

char* get_mpu6050(int a)
{
  	s = ""; 
    switch (a) 
    {	
    	case 0:	/* Aceler X */
    	sprintf(buffer, "%.2f",( ((slave_read_byte(ACCEL_XOUT_H) << 8) | slave_read_byte(ACCEL_XOUT_H + 1) ) / 1638.4 ) );
    	s=buffer;
        return s ; 
        case 1:	/* Aceler Y */
    	sprintf(buffer, "%.2f",( ((slave_read_byte(ACCEL_YOUT_H) << 8) | slave_read_byte(ACCEL_YOUT_H + 1) ) / 1638.4 ) );
    	s=buffer;
        return s ; 
        case 2:
		sprintf(buffer, "%.2f",( ((slave_read_byte(ACCEL_ZOUT_H) << 8) | slave_read_byte(ACCEL_ZOUT_H + 1) ) / 1638.4 ) );
    	s=buffer;
        return s ; /* Aceler Z */
        case 3:
    	sprintf(buffer, "%.2f",( ((slave_read_byte(GYRO_XOUT_H) << 8) | slave_read_byte(GYRO_XOUT_H + 1) ) / 131.0 ) );
    	s=buffer;
        return s ; /* Gyrosc X */
        case 4:
    	sprintf(buffer, "%.2f",( ((slave_read_byte(GYRO_YOUT_H) << 8) | slave_read_byte(GYRO_YOUT_H + 1) ) / 131.0 ) );
    	s=buffer;
        return s ; /* Gyrosc Y */
        case 5:
    	sprintf(buffer, "%.2f",( ((slave_read_byte(GYRO_ZOUT_H) << 8) | slave_read_byte(GYRO_ZOUT_H + 1) ) / 131.0 ) );
    	s=buffer;
        return s ; /* Gyrosc Z */
    }
    return "0";
}

bool slave_write_byte(uint8_t reg_addr, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU6050_SENSOR_ADDR << 1, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    int ret = i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_FAIL) {
        return false;
    }
    return true;
}

int8_t slave_read_byte(uint8_t addr) 
{

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, MPU6050_SENSOR_ADDR << 1, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, addr, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);

    uint8_t buf;
    int8_t d;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    i2c_master_write_byte(cmd, MPU6050_SENSOR_ADDR << 1 | 1, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &buf, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);

    
    d=buf;
    return d;
}
