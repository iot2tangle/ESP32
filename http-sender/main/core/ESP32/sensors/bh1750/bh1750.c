#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "bh1750.h"

char buffer[100];
char* s;

bool check_bh1750()
{
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BH1750_SENSOR_ADDR << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, BH1750_CMD_START, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK)
    	return true;
    else
    	return false;
}

void init_bh1750(bool _ft)
{
	;// Not necesary in this case
}
 
void print_bh1750()
{   
    if (check_bh1750())
		printf("BH1750 : OK");
    else
		printf("BH1750 : Not detected (Light sensor)");
}

char* get_bh1750()
{
    uint8_t data_h, data_l;
    float d;
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();	// Command link Create
    i2c_master_start(cmd);						// Start bit 
    i2c_master_write_byte(cmd, BH1750_SENSOR_ADDR << 1 | WRITE_BIT, ACK_CHECK_EN);		// Write an single byte address
    i2c_master_write_byte(cmd, BH1750_CMD_START, ACK_CHECK_EN);
    i2c_master_stop(cmd);	// Stop bit
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BH1750_SENSOR_ADDR << 1 | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &data_h, ACK_VAL);
    i2c_master_read_byte(cmd, &data_l, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    d = (data_h << 8 | data_l) / 1.2;
    
    s = " ";
    sprintf(buffer, "%.02f", d);
    s=buffer;
    return s;
}
