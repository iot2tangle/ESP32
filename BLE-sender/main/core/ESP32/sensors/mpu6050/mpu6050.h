#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <stdbool.h>

bool check_mpu6050(void);
void init_mpu6050(bool);
void print_mpu6050(void);
char* get_mpu6050(int);

#endif
