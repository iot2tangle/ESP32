#ifndef ESP32_HEADERS_H
#define ESP32_HEADERS_H

#include "basics.h"
#include "gpio/gpio.h"
#include "tIntern/tIntern.h"
#include "bme280/bme280.h"
#include "mpu6050/mpu6050.h"
#include "bh1750/bh1750.h"
#include "acoustic/acoustic.h"

#ifdef MICROCONTROLLER
	#include "wifi/wifi.h"
#endif

#ifdef HTTP
	#include "http-socket/http-socket.h"
#endif

#ifdef MQTT
	#include "mqtt-socket/mqtt-socket.h"
#endif

#endif
