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
   
   bool isEnable_relay[4];

   long interv; 
   
   char json[1023];
}; 

#endif
