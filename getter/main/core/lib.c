#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "struct-device.h"
#include "json/struct-json.h"
#include "json/decoder-i2t-json.h"
#include "config.h"
#include "devices.h"

/*** ACTION/PERFORMANCE FUNCTION *** This is the function where you will define the actions to be performed from the data retrieved from Tangle **/
void action(struct json *j)	
{
	if (j->relative_timestamp < 300)	// If the delay is greater than 300 seconds (5 minutes) it is possible that the Streams channel is not receiving any more messages
	{	
		
	   /*****************************
	   	*							*
		*							*
		*	HERE MUST BE YOUR CODE	*
		*							*
		*							*
		*****************************/

		printf("\nACTIONS:	(Relay 1, 2, 3 and 4 Available)\n");
		printf("\n  ********************************************\n"
			     "  *   You must place your own actions here   *\n"
			     "  ********************************************\n");

		#ifdef EXAMPLE		// This code will not run
		
		/********* Important Tools	*********************************************************************************/
		// 																											//
		//	int value_integer1 = atoi("43");			// atoi() function convert char* (string) to integer		//
		// 	int value_integer2 = atoi(j->sensor[2].value[0]);														//
		// 																											//
		//	float value_float1 = atof("43");			// atof() function convert char* (string) to float			//
		// 	float value_float2 = atof(j->sensor[2].value[1]);														//
		// 																											//
		//	bool isActive;																							//
		//	if (strcmp(j->sensor[2].value[1],"High" == 0)		// strcmp(char*,char*) function compare 2 strings	//
		//		isActive == true;																					//
		//																											//
		/************************************************************************************************************/
		
		/********** EXAMPLES ****************************************************************************************/
		printf("\nACTIONS EXAMPLES:\n");
		/* TEMPERATURE SENSOR EXAMPLE */
		// Suppose that the value of environment temperature is in the variable j->sensor[1].value[0]
		float temperature = atof(j->sensor[1].value[0]);
		
		printf("Temperature Sensor Example       -> ");
		if (temperature > 35.0)			// If temperature is greater than 35 Celsius degrees, Turn on Refrigeration Equipment
		{
			set_relay_GPIO(0, 1);  // Put in HIGH RELAY 1
			printf("High Temperature detected: Turning ON the Refrigeration Equipment\n\n");
		}
		else if (temperature < 30.0)	// If temperature is lower than 30 Celsius degrees, Turn off Refrigeration Equipment
		{
			set_relay_GPIO(0, 0);  // Put in LOW RELAY 1
			printf("Low Temperature: Refrigeration Equipment OFF\n\n");
		}
		
		/* HUMIDITY SENSOR EXAMPLE */
		// Suppose that the value of environment humidity is in the variable j->sensor[1].value[1]
		float humidity = atof(j->sensor[1].value[1]);
		
		printf("Humidity Sensor Example       -> ");
		if (humidity < 40.0)			// If humidity of the soil is lower than 40%, Turn on Irrigation Equipment
		{
			set_relay_GPIO(1, 1);  // Put in HIGH RELAY 2
			printf("Low Humidity in the soil detected: Turning ON the Irrigation System\n\n");
		}
		else if (humidity > 60.0)	// If humidity of the soil is higher than 60%, Turn off Irrigation Equipment
		{
			set_relay_GPIO(1, 0);  // Put in LOW RELAY 2
			printf("Good Humidity in the soil: Irrigation System OFF\n\n");
		}

		/* ACCELERATION SENSOR EXAMPLE */
		// Suppose that this sensor is install in my car to detect when I leave my work, so that my home coffeemaker starts making my coffee
		// the value of Acceleration in X is in the variable j->sensor[5].value[0]
		float x_accel = atof(j->sensor[4].value[0]);
		int time_now = 1613;		//	Actual day hour: 16:13 hs
		if (x_accel > 2.3 && time_now > 1600)	// If acceleration in X is greater than 2.3 m/s2 (the car is running) and the actual time is greater than 16:00hs (my time off from work), Turn on my home coffeemaker
		{
			set_relay_GPIO(2, 1);  // Put in HIGH RELAY 3
			printf("Acceleration in X Sensor Example       -> Car Movement detected: Turning ON home Coffeemaker\n\n");
		}

		/* Acoustic SENSOR EXAMPLE */
		// Suppose that on sound/acoustic level sensor is install in one conference room, and we want to detect when there are many people to have the emergency services ready in case something happens. We will previously set a sound level that indicates that there are many people in the room.
		// the value of environment sound level is in the variable j->sensor[2].value[0]
		if (strcmp(j->sensor[2].value[0],"High") == 0)
		{
			printf("Acoustic Level Sensor Example       -> Acoustic Level exceeded: Activating Security Protocols\n\n");
			// Blinks 2 times
			set_relay_GPIO(3, 1);  // Put in HIGH RELAY 4
			udelay_basics ( 800000 );
			set_relay_GPIO(3, 0);  // Put in LOW RELAY 4
			udelay_basics ( 800000 );
			set_relay_GPIO(3, 1);  // Put in HIGH RELAY 4
			udelay_basics ( 800000 );
			set_relay_GPIO(3, 0);  // Put in LOW RELAY 4
		}

udelay_basics ( 2500000 );
printf("Finished\n");

		#endif
	
	}
}
/***************************************************************/

void config(struct device *z)
{   
    /* User assignments */
    z->id = id_name;
        
    z->addr = address;
    z->addr_port = port;

    #ifdef MQTT
    	z->user_mqtt = user;
	    z->pass_mqtt = password;
	    z->top = topic;
    #endif

    #ifdef MICROCONTROLLER
        z->ssid_wifi = ssid_WiFi;
        z->pass_wifi = pass_WiFi;
    #endif

    z->isEnable_relay[0] = isEnable_Relay_1;
    z->isEnable_relay[1] = isEnable_Relay_2;
    z->isEnable_relay[2] = isEnable_Relay_3;
    z->isEnable_relay[3] = isEnable_Relay_4;

    z->interv = interval;

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
    init_relay();
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

void connectNetwork(struct device *z, bool first_t)
{	
	#ifdef MICROCONTROLLER			
	if (first_t)
	{				
		while ( !connectAttempt(z->ssid_wifi, z->pass_wifi) )    /* Attempt to connect to the network via WiFi, in RaspberryPi only check connection to the network. */
		{
			led_blinks(0, 1, 600000);	// Blink in green GREEN - ERROR 0 (No WiFi connection);
			led_blinks(1, 1, 600000);	// Blink in green RED - ERROR 0 (No WiFi connection);
		}
	}
	#endif
	if ( !init_socket(z->addr, z->addr_port, z->user_mqtt, z->pass_mqtt, first_t) )     /* Check Endpoint */
	{	
		udelay_basics ( 100000 );
		led_blinks(1, 3, 70000);	// Blink in green RED - ERROR 1 (Bad connection with the endpoint);
	}
}

bool get_data_tangle(char* js, struct device *z, long* c)
{
	++(*c);
	d_collect_msg(c);
	
	bool b_socket = get_json(js, z->addr, z->addr_port, z->top, z->user_mqtt, z->pass_mqtt, z->interv);
    if (b_socket)
		led_blinks(0, 2, 60000);	// Blink in green LED;
    else
		led_blinks(1, 3, 70000);	// Blink in green RED - ERROR 1 (Bad connection with the endpoint);
	print_json(js);
	
    return true;
}


void decode_json(char* js, struct json *j)
{
   	printf ("Decoding I2T Json...");
	if ( recover_json(js, j) )
	{
		printf ("		Decoding completed successfully\n\nAvailable Variables in Device '%s' (according to last Json received):\n", j->id);
		for (int i=0; i < MAX_SENSORS; i++)
		{	
			if (j->sensor[i].isEnable)
			{
				printf ("    - Sensor[%d] -> %s    -- ", i, j->sensor[i].id);
				for (int k=0; k < j->sensor[i].num_values; k++)
				{
					printf ("'%s.%s' - ", j->sensor[i].id, j->sensor[i].name[k]);
				}
				printf ("\n");
			}
		}
		j->relative_timestamp = 12;
		printf("        -- Data published in Tangle %ld seconds ago -- (Harcoded value, this feature is not available yet)\n", j->relative_timestamp);
	}
	else
		printf ("\nThe Json is not I2T format, please use the -Json Iot2Tangle format- to decode\n");
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
