#ifndef __BME280_H__
#define __BME280_H__


#include <stdbool.h>

void init_bme280(bool);
bool check_bme280(void);
char* get_bme280(int ind);
void print_bme280(void);

#endif
