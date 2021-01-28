#ifndef _LIB_
#define _LIB_
#include "lib.c"
#include "struct-device.h"

void led_blinks (int, int, int);
void config(struct device *, struct gatt *);
void createServer_BLE(struct device *, struct gatt *);
void initPeripherals(long *); 
void pnp_sensors();
void getData(struct device *,long *, struct gatt *ble);
void updateData_BLE(struct device *, struct gatt *);
void t_delay(long, long); 
long take_time();

#endif
