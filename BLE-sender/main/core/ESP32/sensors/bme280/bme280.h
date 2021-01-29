#ifndef __BME280_H__
#define __BME280_H__

#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#define TICK_DELAY 10

#define I2C_PORT_NUMBER 1

#define BME280_SENSOR_ADDR  0x76	/*Device Address/Identifier */
#define WRITE_BIT 			I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT 			I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 		0x1                        /*!< I2C master will check ack from slave*/


#define BME280_REGISTER_DIG_T1        0x88
#define BME280_REGISTER_DIG_T2        0x8A
#define BME280_REGISTER_DIG_T3        0x8C
#define BME280_REGISTER_DIG_P1        0x8E
#define BME280_REGISTER_DIG_P2        0x90
#define BME280_REGISTER_DIG_P3        0x92
#define BME280_REGISTER_DIG_P4        0x94
#define BME280_REGISTER_DIG_P5        0x96
#define BME280_REGISTER_DIG_P6        0x98
#define BME280_REGISTER_DIG_P7        0x9A
#define BME280_REGISTER_DIG_P8        0x9C
#define BME280_REGISTER_DIG_P9        0x9E
#define BME280_REGISTER_DIG_H1        0xA1
#define BME280_REGISTER_DIG_H2        0xE1
#define BME280_REGISTER_DIG_H3        0xE3
#define BME280_REGISTER_DIG_H4        0xE4
#define BME280_REGISTER_DIG_H5        0xE5
#define BME280_REGISTER_DIG_H6        0xE7
#define BME280_REGISTER_CHIPID        0xD0
#define BME280_REGISTER_VERSION       0xD1
#define BME280_REGISTER_SOFTRESET     0xE0
#define BME280_RESET                  0xB6
#define BME280_REGISTER_CAL26         0xE1
#define BME280_REGISTER_CONTROLHUMID  0xF2
#define BME280_REGISTER_CONTROL       0xF4
#define BME280_REGISTER_CONFIG        0xF5
#define BME280_REGISTER_PRESSUREDATA  0xF7
#define BME280_REGISTER_TEMPDATA      0xFA
#define BME280_REGISTER_HUMIDDATA     0xFD

#define MEAN_SEA_LEVEL_PRESSURE       1013

/*
* Immutable calibration data read from bme280
*/
typedef struct
{
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;

  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;

  uint8_t  dig_H1;
  int16_t  dig_H2;
  uint8_t  dig_H3;
  int16_t  dig_H4;
  int16_t  dig_H5;
  int8_t   dig_H6;
} bme280_calib_data;

/*
* Raw sensor measurement data from bme280
*/
typedef struct 
{
  uint8_t pmsb;
  uint8_t plsb;
  uint8_t pxsb;

  uint8_t tmsb;
  uint8_t tlsb;
  uint8_t txsb;

  uint8_t hmsb;
  uint8_t hlsb;

  uint32_t temperature;
  uint32_t pressure;
  uint32_t humidity;  

} bme280_raw_data;


uint8_t slave_read_ubyte(uint8_t);
bool slave_write_byte_bme280(uint8_t, uint8_t); 
uint16_t slave_read_u16(uint8_t addr);
void init_bme280(bool);
bool check_bme280(void);
char* get_bme280(int ind);
void print_bme280(void);
void readCalibrationData(bme280_calib_data *cal);
int32_t getTemperatureCalibration(bme280_calib_data *cal, int32_t adc_T);
float compensateTemperature(int32_t t_fine);
float compensatePressure(int32_t adc_P, bme280_calib_data *cal, int32_t t_fine);
float compensateHumidity(int32_t adc_H, bme280_calib_data *cal, int32_t t_fine);
void getRawData(bme280_raw_data *raw);

#endif
