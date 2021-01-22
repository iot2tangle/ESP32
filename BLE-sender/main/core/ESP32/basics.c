#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include "basics.h"
#include "sensors/bme280/bme280.h"
#include "sensors/mpu6050/mpu6050.h"
#include "sensors/bh1750/bh1750.h"
#include "sensors/acoustic/acoustic.h"

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
    printf("\n					----  ESP32 -- IOT2TANGLE  --  BLE  ----\n\n");
} 

void d_collect_msg(long* n)
{
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf ("Data collect - %ld\n", *n);
}

void print_sensors_state()
{
	printf ("   Sensors Detection:  ||	");
	print_bme280();
	printf("	||	");
	print_mpu6050();
	printf("	||	");
	print_bh1750();
	printf("	||	");
	print_acoustic();
	printf ("	||\n");
}

void print_json(char* js)
{
    printf("\nJSON: %s\n", js);
    printf("\n	Sending Data to Tangle...\n");
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
