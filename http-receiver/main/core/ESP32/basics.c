#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"

/* ESP32 FreeRTOS DEPENDENCIES */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "nvs_flash.h"

char buffer[100];
char* s;

void welcome_msg()
{
    printf("\n					----  ESP32 KEEPER -- IOT2TANGLE  --");
    
    #ifdef HTTP	
    	printf("  HTTP  ----\n\n");	// Printf in shell
    #endif
    #ifdef MQTT	
    	printf("  MQTT  ----\n\n");	// Printf in shell
    #endif 
} 

void d_collect_msg(long* n)
{
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf ("Data collect from Tangle: - %ld\n", *n);
}

void print_json(char* js)
{
	printf ("Last Json recovered from Tangle:\n%s\n\n", js);
}

void udelay_basics (long d)
{
    vTaskDelay( (d/1000) / portTICK_PERIOD_MS);
}

long take_time_basics()
{
    time_t t;
    time(&t);
    return t;
}

void restart_basic()
{
	esp_restart();		/* Reboot ESP32 */
}
