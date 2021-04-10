#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */


/* Device */
const char* id_name = "ESP32-HTTP";

/* Network Configuration */
const char* ssid_WiFi = "FTTH-BELBRUNO.M";
const char* pass_WiFi = "redbba12";

/* HTTP Endpoint Configuration */
const char* address = "192.168.1.115/sensor_data";  /* Endpoint address (HTTP), must NOT include 'http://xxx' or 'tcp://xxx' */
int port = 8080;

/* Enable Sensors */
bool isEnable_TemperatureIntern = true;
bool isEnable_TemperatureExtern = false;	/*                     true: Enable  --  false: Disable                            */
bool isEnable_Humidity = false;		/* If the sensor is disabled the data about it will not be displayed in the Tangle */
bool isEnable_Pressure = false;
bool isEnable_Acoustic = false;
bool isEnable_Light = true;
bool isEnable_Accelerometer_X = true;
bool isEnable_Accelerometer_Y = true;
bool isEnable_Accelerometer_Z = true;
bool isEnable_Gyroscope_X = true;
bool isEnable_Gyroscope_Y = true;
bool isEnable_Gyroscope_Z = true;

/* Interval of time */
long interval = 30;    /* Time in seconds between */


#endif
