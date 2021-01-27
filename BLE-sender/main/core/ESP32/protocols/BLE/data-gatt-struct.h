#ifndef DATA_DEVICE_H_
#define DATA_DEVICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SERVICE_MAX_TAM 7
#define CHARACT_MAX_TAM 6

struct gatt {

	uint8_t service_TAM;
	uint8_t charact_TAM[SERVICE_MAX_TAM];
	
	const char *service_name[30][SERVICE_MAX_TAM];
	uint8_t service_handle[SERVICE_MAX_TAM];
	
	const char *charact_name[30][SERVICE_MAX_TAM][CHARACT_MAX_TAM];
	char *charact_data[30][SERVICE_MAX_TAM][CHARACT_MAX_TAM];
}; 

#endif
