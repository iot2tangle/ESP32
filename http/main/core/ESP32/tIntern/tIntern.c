#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tIntern.h"

char buffer[400];
char *s;
float data;

char* get_internal_temp() 
{
    s = " ";

//  READ SENSOR DATA
    data = 57.3;

    sprintf(buffer, "%.2f", data);

    s=buffer;
    return s; /* Light */   
}

