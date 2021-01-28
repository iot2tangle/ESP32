#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "devices.h"
#include "ESP32/protocols/BLE/BLE.h"
#include "ESP32/protocols/BLE/data-gatt-struct.h"


void config(struct gatt *ble)
{   
    /* User assignments */
    strcpy(ble->id, id_name);
    
    ble->service_TAM=6;
    
    // First Sensor
    strcpy(ble->service_name[0], "Internal");
    ble->charact_TAM[0] = 1;
    	strcpy(ble->charact_name[0][0], "InternalTemperature"); 
    	ble->isEnable[0][0] = isEnable_TemperatureIntern;

    // Second Sensor
    strcpy(ble->service_name[1], "Enviromental");
    ble->charact_TAM[1] = 3;
    	strcpy(ble->charact_name[1][0], "Temperature"); 
    	ble->isEnable[1][0] = isEnable_TemperatureExtern;
    	strcpy(ble->charact_name[1][1], "Humidity"); 
    	ble->isEnable[1][0] = isEnable_Humidity;
    	strcpy(ble->charact_name[1][2], "Pressure"); 
    	ble->isEnable[1][0] = isEnable_Pressure;
    
    // Third Sensor
    strcpy(ble->service_name[2], "Acoustic");
    ble->charact_TAM[2] = 1;
    	strcpy(ble->charact_name[2][0], "SoundLevel"); 
    	ble->isEnable[2][0] = isEnable_TemperatureExtern;
    	
    // Fourth Sensor
    strcpy(ble->service_name[3], "Light");
    ble->charact_TAM[3] = 1;
    	strcpy(ble->charact_name[3][0], "Light"); 
    	ble->isEnable[3][0] = isEnable_TemperatureExtern;
    	   
    // Fifth Sensor
    strcpy(ble->service_name[4], "Accelerometer");
    ble->charact_TAM[4] = 3;
    	strcpy(ble->charact_name[4][0], "X"); 
    	ble->isEnable[4][0] = isEnable_TemperatureExtern;
    	strcpy(ble->charact_name[4][1], "Y"); 
    	ble->isEnable[4][0] = isEnable_Humidity;
    	strcpy(ble->charact_name[4][2], "Z"); 
    	ble->isEnable[4][0] = isEnable_Pressure;  

    // Sixth Sensor
    strcpy(ble->service_name[5], "Gyroscope");
    ble->charact_TAM[5] = 3;
    	strcpy(ble->charact_name[5][0], "X"); 
    	ble->isEnable[5][0] = isEnable_TemperatureExtern;
    	strcpy(ble->charact_name[5][1], "Y"); 
    	ble->isEnable[5][0] = isEnable_Humidity;
    	strcpy(ble->charact_name[5][2], "Z"); 
    	ble->isEnable[5][0] = isEnable_Pressure;

}

void initPeripherals(long* c) 
{
    *c = 0;		// Init counter
    
    #ifdef SHELLPRINT
    	welcome_msg();	// Printf in shell
    #endif
	
    init_LEDs();
    init_i2c();
    init_SPI();
	
	init_internal(true);
    init_bme280(true);
    init_mpu6050(true);
    init_bh1750(true);
    init_acoustic(true);
}


void led_blinks(int led, int iter, int usec)	// LED Blink function-> led: 0 Green LED, 1 Red LED - iter: iterations quantity - usec: delay time in usec
{	
    int i;
    for (i=0;i<iter;i++)
    {
	led_GPIO(led, 1);
	udelay_basics (usec);
	led_GPIO(led, 0);
	udelay_basics (usec);
    }
}

void createServer_BLE(struct gatt *ble)
{	
	ble_socket(ble);
	printf("  CREATED BLE SERVER\n");
}

void pnp_sensors()
{
    init_bme280(false);
    init_mpu6050(false);	
    init_bh1750(false);	
    init_acoustic(false);
}


void updateData(long *c, struct gatt *ble)
{
    int i;
    ++(*c);
	
    #ifdef SHELLPRINT	// Printf in shell
	d_collect_msg( c );
	print_sensors_state();
    #endif  

	
    /* GET DATA INTERNAL TEMPERATURE */
    strcpy(ble->charact_data[0][0], get_internal());
	
    /* GET DATA BME280 */
    if (check_bme280())
    {
		for (i=0; i<3; i++)
	   	    strcpy(ble->charact_data[1][i], get_bme280(i));
    }
    else
    {
		for (i=0; i<3; i++)
			strcpy(ble->charact_data[1][i], "0");
    }

    /* GET DATA ACOUSTIC */
    if (check_acoustic())
		strcpy(ble->charact_data[2][0], get_acoustic());
    else	
		strcpy(ble->charact_data[2][0], "0");

    /* GET DATA LIGHT */
    if (check_bh1750())
		strcpy(ble->charact_data[3][0], get_bh1750());
    else
		strcpy(ble->charact_data[3][0], "0");


    /* GET DATA MPU6050 */
    if (check_mpu6050())
    {
		for (i=0; i<3; i++)
		{
			strcpy(ble->charact_data[4][i], get_mpu6050(i));
			strcpy(ble->charact_data[5][i], get_mpu6050(i+3));
		}
    }
    else
    {
	 	for (i=0; i<3; i++)
	 	{
			strcpy(ble->charact_data[4][i], "0");
			strcpy(ble->charact_data[5][i], "0");
		}
    }
    
}

void t_delay(long d, long l) 
{  
	if (l >= d)		/* To prevent crashes */
		l = d;
    udelay_basics ( (d - l) * 1000000 );	/* Time set by user  minus  loss time by operation */ 
}

long take_time() 
{  
    return take_time_basics();
}


