#ifndef _CONFIG_H
#define _CONFIG_H

/* ----- CONFIG FILE ----- */


/* Device */
const char* id_name = "ESP32-GETTER";

/* Network Configuration */
const char* ssid_WiFi = "mySSID";
const char* pass_WiFi = "myPASS";

/* HTTP Endpoint Configuration */
const char* address = "192.168.1.101/sensor_data";  /* Endpoint address (HTTP), must NOT include 'http://xxx' or 'tcp://xxx', and must include '/sensor_data' for using in I2T Gateway*/
int port = 8080;

/* Enable Relays */
bool isEnable_Relay_1 = true;
bool isEnable_Relay_2 = true;	/*			true: Enable  --  false: Disable			*/
bool isEnable_Relay_3 = true;


/* Interval of time */
long interval = 30;    /* Time in seconds between */


#endif
