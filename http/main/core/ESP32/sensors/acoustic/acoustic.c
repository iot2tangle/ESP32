#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "acoustic.h"

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define ACOUSTIC_ENABLE 22	// GPIO 23
#define ACOUSTIC_DATA 21 // GPIO 22

char buffer[100];
char* s;

bool check_acoustic()
{
    if ( gpio_get_level(ACOUSTIC_ENABLE) ) 
	return false;
    else
    	return true;	
}

void init_acoustic(bool ft)
{
    gpio_pad_select_gpio(ACOUSTIC_ENABLE);
    gpio_set_direction(ACOUSTIC_ENABLE, GPIO_MODE_INPUT);
    gpio_set_pull_mode(ACOUSTIC_ENABLE, GPIO_PULLUP_ONLY);	// Set PullUp
    
    gpio_pad_select_gpio(ACOUSTIC_DATA);
    gpio_set_direction(ACOUSTIC_DATA, GPIO_MODE_INPUT);
    gpio_set_pull_mode(ACOUSTIC_DATA, GPIO_PULLDOWN_ONLY);	// Set PullDown
} 

void print_acoustic()
{
    if (check_acoustic())
	printf("SOUND Sensor : OK");
    else
	printf("SOUND Sensor : Not detected");
}

char* get_acoustic()
{
    s = " ";

    if ( gpio_get_level(ACOUSTIC_DATA) ) 
	sprintf(buffer, "High");
    else
	sprintf(buffer, "Low");

    s=buffer;
    return s;
}


