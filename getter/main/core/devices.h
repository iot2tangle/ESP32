#ifndef _DEVICES_H_
#define _DEVICES_H_

#ifdef RASPI
	#include "raspi3-4/raspi3-4-headers.h"
#endif
#ifdef MYDEVICE
	#include "my-device/my-device-headers.h"
#endif
#ifdef ESP32
	#include "ESP32/ESP32-headers.h"
#endif

#endif
