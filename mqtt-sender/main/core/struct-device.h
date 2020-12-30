#ifndef STRUCT_DEVICE_H_
#define STRUCT_DEVICE_H_

#include <stdio.h>
#include <stdbool.h>


struct device {
   const char *id;

   const char *addr;
   int addr_port;
   const char *top;    
   const char *user_mqtt;
   const char *pass_mqtt;   


   const char *ssid_wifi;
   const char *pass_wifi;
   
   bool isEnable[12];
   char d[12][10];    /* Sensors Data String */
   const char *s_name[30];    /* Sensors Names */
   bool isConnected[12];

   long interv; 
   
   char json[1023];
}; 

#endif
