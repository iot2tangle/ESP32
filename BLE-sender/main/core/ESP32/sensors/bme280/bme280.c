#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bme280.h"

char buffer[100];
char* s;

float data[3];

bool check_bme280()
{   
	// IF BME280 IS DETECTED  
	return true;
}

void init_bme280(bool ft)
{   
	; // INIT BME280  
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
    
    // READ DATA IND	:	0 - Temperature, 1 - Humidity, 2 - Pressure 
   data[0] = 25.3;
   data[1] = 43.3;
   data[2] = 932.4;
   
   
    s = " ";
  
    if (ind == 0)
    {
	sprintf(buffer, "%.2f", data[0]);
	s=buffer;
	return s ; /* Celsius */
    }
    if (ind == 1)
    {
	sprintf(buffer, "%.2f", data[1] );
	s=buffer;
	return s ; /* % */
    }
    if (ind == 2)
    {
	sprintf(buffer, "%.1f", data[2] );
	s=buffer;
	return s ; /* hPa */
    }
    return 0;
}
