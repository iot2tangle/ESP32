#ifndef ESP32_HEADERS_H
#define ESP32_HEADERS_H

#include "basics.h"
#include "peripherals/gpio/gpio.h"
#include "peripherals/i2c/i2c.h"
#include "peripherals/spi/spi.h"
#include "output/relay/relay.h"

#ifdef MICROCONTROLLER
	#include "wifi/wifi.h"
#endif

#ifdef HTTP
	#include "protocols/http/http.h"
#endif

#ifdef MQTT
	#include "protocols/mqtt/mqtt.h"
#endif

#endif
