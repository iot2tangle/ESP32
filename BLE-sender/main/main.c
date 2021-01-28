#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "core/lib.h"
#include "core/struct-device.h"
#include "core/ESP32/protocols/BLE/data-gatt-struct.h"

struct device dev;
struct gatt ble;

long count, init_t;

int main ()
{	
    config(&dev, &ble);			/* Configure Name of the device, Endpoint address and Wifi credentials (if its a WiFi Connection), return string with the endpoint */	
    initPeripherals(&count);	/* Init GPIOs, I2C and ADC */
    createServer_BLE(&dev, &ble);	/* Will drop out of this structure only when it has connected to the network and checks the existence of the endpoint */

    while (1)
    {	
	    init_t = take_time();

	    pnp_sensors();		/* re init sensors to be able to plug n play in real time */

	    getData(&dev, &count, &ble);

	    updateData_BLE(&dev, &ble);

	    t_delay(dev.interv, take_time() - init_t);  /* compensated delay */
    }    
    return 0;
}
