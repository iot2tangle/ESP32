#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bh1750.h"

char buffer[100];
char* s;

int data;

bool check_bh1750()
{
	// IF BH1750 IS DETECTED  
	return true;
}

void init_bh1750(bool ft)
{
	; // INIT BH1750
} 

void print_bh1750()
{   
    if (check_bh1750())
	printf("BH1750 : OK");
    else
	printf("BH1750 : Not detected (Light sensor)");
}
	
char* get_bh1750()
{
    s = " ";

//  READ SENSOR DATA
    data = 230;

    sprintf(buffer, "%d", data);

    s=buffer;
    return s; /* Light */
}

