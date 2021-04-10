#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "internal.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temp_sensor.h"

char buffer[400];
char *s;
float data;

float tsens_out;

void init_internal(bool ft)
{
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor_get_config(&temp_sensor);
    temp_sensor.dac_offset = TSENS_DAC_DEFAULT; // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

char* get_internal() 
{
    s = " ";

//  READ SENSOR DATA
	temp_sensor_read_celsius(&tsens_out);

    sprintf(buffer, "%.2f", tsens_out);

    s=buffer;
    return s; /* Celsius */   
}

