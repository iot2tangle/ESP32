#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "internal.h"

char buffer[400];
char *s;
float data;

void init_internal(bool ft)
{
	;
}

char* get_internal() 
{
    s = " ";

//  READ SENSOR DATA
    data = 57.3;

    sprintf(buffer, "%.2f", data);

    s=buffer;
    return s; /* Light */   
}

