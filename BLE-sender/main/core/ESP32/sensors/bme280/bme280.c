#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "bme280.h"

// BME280 not working well in this version yet

int fd_bme;
bme280_calib_data cal;
bme280_raw_data raw;
int32_t t_fine;
int id_bme280;

char buffer[100];
char* s;

bool check_bme280()
{   
	int ret;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK)
    	return true;
    else
    	return false;
}

void init_bme280(bool ft)
{   
	slave_write_byte_bme280(BME280_REGISTER_CONTROLHUMID, 0x01);		// humidity oversampling x 1
	slave_write_byte_bme280(BME280_REGISTER_CONTROL, 0x25);		// pressure and temperature oversampling x 1, mode normal	
}

void print_bme280()
{
    if (check_bme280())
		printf("BME280 : OK");
    else
		printf("BME280 : Not detected (Temperat, Humidity, Pressure sensor)");
}

char* get_bme280(int ind) 
{
    readCalibrationData(&cal);
    getRawData(&raw);
    t_fine = getTemperatureCalibration(&cal, raw.temperature);
    s = " ";
  
    if (ind == 0)
    {
	//sprintf(buffer, "%.2f", compensateTemperature(t_fine));
	sprintf(buffer, "%.2f", ((raw.temperature/8388.6) - 40) );
	s=buffer;
	return s ; 
    }
    if (ind == 1)
    {
	//sprintf(buffer, "%.2f", compensateHumidity(raw.humidity, &cal, t_fine) );
	sprintf(buffer, "%.2f", (raw.humidity/355.4) );
	s=buffer;
	return s ; 
    }
    if (ind == 2)
    {
	//sprintf(buffer, "%.1f", compensatePressure(raw.pressure, &cal, t_fine) / 100 );
	sprintf(buffer, "%.2f", ((raw.pressure/1310.7) + 300) );
	s=buffer;
	return s ; 
    }
    return "0";
}


int32_t getTemperatureCalibration(bme280_calib_data *cal, int32_t adc_T) 
{
    int32_t var1  = ((((adc_T>>3) - ((int32_t)cal->dig_T1 <<1))) * ((int32_t)cal->dig_T2)) >> 11;

    int32_t var2  = (((((adc_T>>4) - ((int32_t)cal->dig_T1)) * ((adc_T>>4) - ((int32_t)cal->dig_T1))) >> 12) * ((int32_t)cal->dig_T3)) >> 14;

    return var1 + var2;
}

void readCalibrationData(bme280_calib_data *data) {

    data->dig_T1 = (uint16_t)slave_read_u16(BME280_REGISTER_DIG_T1) + 32768;
    data->dig_T2 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_T2);
    data->dig_T3 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_T3);

    data->dig_P1 = (uint16_t)slave_read_u16(BME280_REGISTER_DIG_P1) + 32768;
    data->dig_P2 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P2);
    data->dig_P3 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P3);
    data->dig_P4 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P4);
    data->dig_P5 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P5);
    data->dig_P6 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P6);
    data->dig_P7 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P7);
    data->dig_P8 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P8);
    data->dig_P9 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_P9);

    data->dig_H1 = (uint8_t)slave_read_u16(BME280_REGISTER_DIG_H1) + 32768;
    data->dig_H2 = (int16_t)slave_read_u16(BME280_REGISTER_DIG_H2);
    data->dig_H3 = (uint8_t)slave_read_u16(BME280_REGISTER_DIG_H3) + 32768;
    data->dig_H4 = (((int8_t)slave_read_ubyte(BME280_REGISTER_DIG_H4)) << 4) | (((int8_t)slave_read_ubyte(BME280_REGISTER_DIG_H4+1)) & 0xF);
    data->dig_H5 = (((int8_t)slave_read_ubyte(BME280_REGISTER_DIG_H5+1)) << 4) | (((int8_t)slave_read_ubyte(BME280_REGISTER_DIG_H5)) >> 4);
    data->dig_H6 = (int8_t)slave_read_ubyte(BME280_REGISTER_DIG_H6);
}

float compensateTemperature(int32_t t_fine) 
{
    float T  = (t_fine * 5 + 128) >> 8;
    return T/100;
}

float compensatePressure(int32_t adc_P, bme280_calib_data *cal, int32_t t_fine) 
{
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)cal->dig_P6;
    var2 = var2 + ((var1*(int64_t)cal->dig_P5)<<17);
    var2 = var2 + (((int64_t)cal->dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)cal->dig_P3)>>8) + ((var1 * (int64_t)cal->dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)cal->dig_P1)>>33;

    if (var1 == 0) 
    {
    	return 0;  // avoid exception caused by division by zero
    }
    p = 1048576 - adc_P;
    p = (((p<<31) - var2)*3125) / var1;
    var1 = (((int64_t)cal->dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)cal->dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)cal->dig_P7)<<4);
    return (float)p/256;
}


float compensateHumidity(int32_t adc_H, bme280_calib_data *cal, int32_t t_fine) 
{
    int32_t v_x1_u32r;

    v_x1_u32r = (t_fine - ((int32_t)76800));

    v_x1_u32r = (((((adc_H << 14) - (((int32_t)cal->dig_H4) << 20) -
      (((int32_t)cal->dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
         (((((((v_x1_u32r * ((int32_t)cal->dig_H6)) >> 10) *
        (((v_x1_u32r * ((int32_t)cal->dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
      ((int32_t)2097152)) * ((int32_t)cal->dig_H2) + 8192) >> 14));

    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
           ((int32_t)cal->dig_H1)) >> 4));

    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    float h = (v_x1_u32r>>12);
    return  h / 1024.0;
}

void getRawData(bme280_raw_data *raw) 
{
    raw->temperature = 0;
    raw->temperature = (raw->temperature | (uint8_t)slave_read_ubyte(BME280_REGISTER_TEMPDATA)) << 8;
    raw->temperature = (raw->temperature | (uint8_t)slave_read_ubyte(BME280_REGISTER_TEMPDATA + 1)) << 8;
    raw->temperature = (raw->temperature | (uint8_t)slave_read_ubyte(BME280_REGISTER_TEMPDATA + 2)) >> 4;

    raw->pressure = 0;
    raw->pressure = (raw->pressure | (uint8_t)slave_read_ubyte(BME280_REGISTER_PRESSUREDATA)) << 8;
    raw->pressure = (raw->pressure | (uint8_t)slave_read_ubyte(BME280_REGISTER_PRESSUREDATA + 1)) << 8;
    raw->pressure = (raw->pressure | (uint8_t)slave_read_ubyte(BME280_REGISTER_PRESSUREDATA + 2)) >> 4;

    raw->humidity = 0;
    raw->humidity = (raw->humidity | (uint8_t)slave_read_ubyte(BME280_REGISTER_HUMIDDATA)) << 8;
    raw->humidity = (raw->humidity | (uint8_t)slave_read_ubyte(BME280_REGISTER_HUMIDDATA + 1));
}

bool slave_write_byte_bme280(uint8_t reg_addr, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1, ACK_CHECK_EN);
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

uint8_t slave_read_ubyte(uint8_t addr) 
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, addr, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);

    uint8_t buf;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1 | 1, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &buf, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    
    return buf;
}

uint16_t slave_read_u16(uint8_t addr)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, addr, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);

    uint8_t buf;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, BME280_SENSOR_ADDR << 1 | 1, ACK_CHECK_EN);
    i2c_master_read(cmd, &buf, 16, 1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_PORT_NUMBER, cmd, TICK_DELAY);
    i2c_cmd_link_delete(cmd);
    
    return buf;
}
