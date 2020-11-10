#ifndef _LIB_
#define _LIB_
#include "lib.c"
#include "struct-device.h"

void led_blinks (int, int, int);
void config(struct device *);
void connectNetwork(struct device *, bool);
void initPeripherals(long *); 
bool get_data_tangle(char*, struct device*, long*);
void decode_json(char*, struct json *);
void t_delay(long, long); 
long take_time();
void clear_data(struct json*);

#endif
