#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */

/* Device */
const char* id_name = "ESP32-BLE";

/* Enable Sensors */
bool isEnable_TemperatureIntern = true;
bool isEnable_TemperatureExtern = true;	/*                     true: Enable  --  false: Disable                            */
bool isEnable_Humidity = true;		/* If the sensor is disabled the data about it will not be displayed in the Tangle */
bool isEnable_Pressure = true;		
bool isEnable_Acoustic = true;
bool isEnable_Light = true;
bool isEnable_Accelerometer_X = true;
bool isEnable_Accelerometer_Y = true;
bool isEnable_Accelerometer_Z = true;
bool isEnable_Gyroscope_X = true;
bool isEnable_Gyroscope_Y = true;
bool isEnable_Gyroscope_Z = true;


/* Interval of time for Data Update  - IMPORTANT: Unlike HTTP or MQTT senders, this interval only updates the data locally (therefore it can be smaller), since the sending data interval to the Tangle is determined by the BLE Gateway, not by the ESP32 as in the previous cases .*/
long interval = 6;    /* Time in seconds */


#endif
