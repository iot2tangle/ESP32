#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "core/lib.h"
#include "core/struct-device.h"
#include "core/json/struct-json.h"

#define JSON_SIZE_MAX 1024

struct device dev;
struct json j;
//char js[JSON_SIZE_MAX];

long count, init_t;

int main ()
{	
    config(&dev);			/* Configure Name of the device, Endpoint address and Wifi credentials (if its a WiFi Connection), return string with the endpoint */	
    initPeripherals(&count);	/* Init GPIOs, I2C and ADC */
    connectNetwork(&dev, true);	/* Will drop out of this structure only when it has connected to the network and checks the existence of the endpoint */ 

    while (1)
    {	
    	char* js = malloc(JSON_SIZE_MAX + 1);
	    init_t = take_time();
	
		if ( !get_data_tangle(js, &dev, &count) )	/* Get data Json from Tangle */
			connectNetwork(&dev, false);	/* Only enters it detects a network error */	
		else
		{
			decode_json(js, &j);	/* Decode the I2T Json */
			action(&j);				/* Execute user actions */
		}
		
		clear_data(&j);
		free(js);	// Free malloc js
	    t_delay(dev.interv, take_time() - init_t);  /* compensated delay */
    }    
    return 0;
}
