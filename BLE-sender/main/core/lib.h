#ifndef _LIB_
#define _LIB_
#include "lib.c"

void led_blinks (int, int, int);
void config(struct gatt *);
void createServer_BLE(struct gatt *);
void initPeripherals(long *); 
void pnp_sensors();
void updateData(long *, struct gatt *ble);
void t_delay(long, long); 
long take_time();

#endif
