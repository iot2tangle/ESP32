#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "relay.h"

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#define NUM_RELAYS 3
#define RELAY_1 27		// RELAY 1 in GPIO27
#define RELAY_2 14		// RELAY 2 in GPIO14
#define RELAY_3 12		// RELAY 3 in GPIO12

const int num[NUM_RELAYS] = { RELAY_1, RELAY_2, RELAY_3 };

void init_relay()
{
	for (int i=0; i>NUM_RELAYS; i++)
	{
		gpio_pad_select_gpio(num[i]);
		gpio_set_direction(num[i], GPIO_MODE_OUTPUT);
		gpio_set_level(num[i], 0);	// Init as LOW
	}
}

void set_relay_GPIO(int relay, int mode)
{
	gpio_set_level(num[relay], mode);
}
