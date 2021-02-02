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
    
    int c = 0;
    
    // First Sensor
    strcpy(ble->service_name[c], "Internal");
    ble->charact_TAM[c] = 2;
    	strcpy(ble->charact_name[c][0], "Internal"); 
    	strcpy(ble->charact_name[c][1], "Temp"); 

    // Second Sensor
    if (isEnable_Environmental)
    {
    	c++;
    	strcpy(ble->service_name[c], "Environmental");
    		ble->charact_TAM[c] = 4;
			strcpy(ble->charact_name[c][0], "Environmen"); 
			strcpy(ble->charact_name[c][1], "Temp"); 
			strcpy(ble->charact_name[c][2], "Humid"); 
			strcpy(ble->charact_name[c][3], "Pressure");
	}
    
    // Third Sensor
    if (isEnable_Acoustic)
    {
    	c++;
		strcpy(ble->service_name[c], "Acoustic");
		ble->charact_TAM[c] = 2;
			strcpy(ble->charact_name[c][0], "Acoustic"); 
			strcpy(ble->charact_name[c][1], "SoundLevel");
	}
    	
    // Fourth Sensor
    if (isEnable_Light)
    {
    	c++;
		strcpy(ble->service_name[c], "Light");
		ble->charact_TAM[c] = 2;
			strcpy(ble->charact_name[c][0], "Light"); 
			strcpy(ble->charact_name[c][1], "Light"); 
	}
    	   
    // Fifth Sensor
    if (isEnable_Accelerometer)
    {
		c++;
			strcpy(ble->service_name[c], "Accelerometer");
			ble->charact_TAM[c] = 4;
				strcpy(ble->charact_name[c][0], "Accelerom"); 
				strcpy(ble->charact_name[c][1], "X"); 
				strcpy(ble->charact_name[c][2], "Y"); 
				strcpy(ble->charact_name[c][3], "Z"); 
	} 

    // Sixth Sensor
    if (isEnable_Gyroscope)
    {
		c++;
		strcpy(ble->service_name[c], "Gyroscope");
		ble->charact_TAM[c] = 4;
			strcpy(ble->charact_name[c][0], "Gyroscope"); 
			strcpy(ble->charact_name[c][1], "X"); 
			strcpy(ble->charact_name[c][2], "Y"); 
			strcpy(ble->charact_name[c][3], "Z"); 
	}
    	
    ble->service_TAM= c+1;
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
    int cnt = 0;
	
    #ifdef SHELLPRINT	// Printf in shell
	d_collect_msg( c );
	print_sensors_state();
    #endif  
	
    /* GET DATA INTERNAL TEMPERATURE */
    strcpy(ble->charact_data[0][1], get_internal());

    /* GET DATA BME280 */
    if (isEnable_Environmental)
    {
    	cnt++;
		if (check_bme280())
		{
			for (i=0; i<3; i++)
		   	    strcpy(ble->charact_data[cnt][i+1], get_bme280(i));
		}
		else
		{
			for (i=0; i<3; i++)
				strcpy(ble->charact_data[cnt][i+1], "");
		}
    }

    /* GET DATA ACOUSTIC */
    if (isEnable_Acoustic)
    {
    	cnt++;
		if (check_acoustic())
			strcpy(ble->charact_data[cnt][1], get_acoustic());
		else	
			strcpy(ble->charact_data[cnt][1], "");
	}

    /* GET DATA LIGHT */
    if (isEnable_Light)
    {
    	cnt++;
		if (check_bh1750())
			strcpy(ble->charact_data[cnt][1], get_bh1750());
		else
			strcpy(ble->charact_data[cnt][1], "");
	}

    /* GET DATA ACCELEROMETER */
	if (isEnable_Accelerometer)
    {
    	cnt++;
		if (check_mpu6050())
		{
			for (i=0; i<3; i++)
				strcpy(ble->charact_data[cnt][i+1], get_mpu6050(i));
		}
		else
		{
		 	for (i=0; i<3; i++)
				strcpy(ble->charact_data[cnt][i+1], "");
		}
	}

    /* GET DATA GYROSCOPE */
	if (isEnable_Gyroscope)
    {
    	cnt++;
		if (check_mpu6050())
		{
			for (i=0; i<3; i++)
				strcpy(ble->charact_data[cnt][i+1], get_mpu6050(i+3));
		}
		else
		{
		 	for (i=0; i<3; i++)
				strcpy(ble->charact_data[cnt][i+1], "");
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


