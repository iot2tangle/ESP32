#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "acoustic.h"

char buffer[100];
char* s;

bool check_acoustic()
{
	// IF ACOUTIC SENSOR IS DETECTED  
	return true;
}

void init_acoustic(bool ft)
{
	; //INIT ACOUSTIC SENSOR
}

void print_acoustic()
{
    if (check_acoustic())
	printf("SOUND Sensor : OK");
    else
	printf("SOUND Sensor : Not detected");
}

char* get_acoustic()
{
    s = " ";

//  READ SENSOR DATA

//  IF SENSOR DATA == HIGH
	sprintf(buffer, "High");
//    else
//	sprintf(buffer, "Low");

    s=buffer;
    return s;
}


