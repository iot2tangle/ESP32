#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */

/* Device */
const char* id_name = "ESP32-BLE-I2T";

/* Enable Sensors */
bool isEnable_Environmental = true;
bool isEnable_Acoustic = true;	/*                     true: Enable  --  false: Disable                            */
bool isEnable_Light = true;		/* If the sensor is disabled the data about it will not be displayed in the Tangle */
bool isEnable_Accelerometer = true;		
bool isEnable_Gyroscope = true;

/* Interval of time for Data Update  - IMPORTANT: Unlike HTTP or MQTT senders, this interval only updates the data locally (therefore it can be smaller), since the sending data interval to the Tangle is determined by the BLE Gateway, not by the ESP32 as in the previous cases .*/
long interval = 6;    /* Time in seconds */

#endif
