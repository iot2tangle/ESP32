#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "core/lib.h"
#include "core/struct-device.h"


struct device dev;

long count, init_t;

int main ()
{	
    config(&dev);			/* Configure Name of the device, Endpoint address and Wifi credentials (if its a WiFi Connection), return string with the endpoint */	
    initPeripherals(&count);	/* Init GPIOs, I2C and ADC */
    connectNetwork(&dev, true);	/* Will drop out of this structure only when it has connected to the network and checks the existence of the endpoint */ 

    while (1)
    {	
	    init_t = take_time();

	    pnp_sensors();		/* re init sensors to be able to plug n play in real time */

	    getData(&dev, &count);

	    generateJson(&dev);

	    if ( !sendtoEndpoint(&dev) )	/* Send JSON to the Endpoint, return boolean with the success of the operation */
			connectNetwork(&dev, false);	/* Only enters it detects a network error */

	    t_delay(dev.interv, take_time() - init_t);  /* compensated delay */
    }    
    return 0;
}
