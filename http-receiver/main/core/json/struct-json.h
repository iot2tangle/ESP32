#ifndef _STRUCT_JSON_H_
#define _STRUCT_JSON_H_

#include <stdio.h>
#include <stdbool.h>

#define MAX_SENSORS 16
#define MAX_VALUE 8

struct s_sensor
{
	bool isEnable;
	char id[32];
	char name[32][MAX_VALUE];
	char value[32][MAX_VALUE];
	int num_values;
};

struct json
{
	int id_keepy;
   	char credential[32];

	struct s_sensor sensor[MAX_SENSORS];

   	char id[32];
	long timestamp, relative_timestamp;
	char channel[110];
}; 

#endif
