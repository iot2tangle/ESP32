#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpu6050.h"

char buffer[100];
char* s;

float data[6];

bool check_mpu6050()
{
	// IF MPU6050 IS DETECTED  
	return true;
}

void init_mpu6050(bool ft)
{
	; // INIT MPU6050 
} 

void print_mpu6050()
{
    if (check_mpu6050())
	printf("MPU6050 : OK");
    else
	printf("MPU6050 : Not detected (Accelerometer, Gyroscope sensor)");
}

char* get_mpu6050(int a)
{
   data[0] = 5.23;
   data[1] = 2.12;
   data[2] = 1.52;
   data[3] = 0.64;
   data[4] = 0.32;
   data[5] = 2.32;
   
    s = ""; 
    switch (a) 
    {	
    	case 0:	/* Aceler X */
    	sprintf(buffer, "%.2f", data[0]);
    	s=buffer;
        return s ; 
        case 1:	/* Aceler Y */
    	sprintf(buffer, "%.2f", data[1]);
    	s=buffer;
        return s ; 
        case 2:
    	sprintf(buffer, "%.2f", data[2]);
    	s=buffer;
        return s ; /* Aceler Z */
        case 3:
    	sprintf(buffer, "%.2f", data[3]);
    	s=buffer;
        return s ; /* Gyrosc X */
        case 4:
    	sprintf(buffer, "%.2f", data[4]);
    	s=buffer;
        return s ; /* Gyrosc Y */
        case 5:
    	sprintf(buffer, "%.2f", data[5]);
    	s=buffer;
        return s ; /* Gyrosc Z */
    }
    return "0";
}

