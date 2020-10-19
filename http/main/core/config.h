#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */


/* Device */
const char* id_name = "MyDevice-I2T";


/* Endpoint/Broker Configuration */
const char* endpoint = "localhost/iot2tangle";  /* Endpoint (HTTP) or Broker address (MQTT), must NOT include 'http://xxx' or 'tcp://xxx' */
int port = 8080;
const char* topic = "iot2tangle";	/* Only for MQTT Protocol, leave empty in HTTP */
const char* user = "user";		/* Only for MQTT Protocol, leave empty in HTTP */
const char* password = "pass";	/* Only for MQTT Protocol, leave empty in HTTP */

/* Network Configuration (Only for microcontrollers) */
bool isWifi = false; /* This is 'true' for microcontrollers like ESP32 or STM32. In RaspberryPi it will be 'false', because the network connection is made outside the program by the Raspberry OS */
const char* ssid_WiFi = "SSID-WIFI";
const char* pass_WiFi = "pass_WiFi";


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

/* Interval of time */
long interval = 10;    /* Time in seconds between */


#endif
