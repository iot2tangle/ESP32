#ifndef _STRUCT_JSON_H_
#define _STRUCT_JSON_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_SENSORS 16
#define MAX_VALUE 8

struct s_sensor
{
	char id[32];
	char name[32][MAX_VALUE];
	char value[32][MAX_VALUE];
};

struct json
{
   	char credential[32];

	struct s_sensor sensor[MAX_SENSORS];

   	char id[32];
	long timestamp, relative_timestamp;
}; 

#endif
