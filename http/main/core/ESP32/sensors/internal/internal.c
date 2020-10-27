#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "internal.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
extern uint8_t temprature_sens_read();

char buffer[400];
char *s;
float data;
float temp_celsius;

void init_internal(bool ft)
{
	;
}

char* get_internal() 
{
    s = " ";

//  READ SENSOR DATA
	temp_celsius= ( temprature_sens_read() - 32 ) / 1.8;

    sprintf(buffer, "%.2f", temp_celsius);

    s=buffer;
    return s; /* Celsius */   
}

