#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jsmn/jsmn.h"
#include "struct-json.h"
#include "decoder-i2t-json.h"

bool recover_json(char* js, struct json *j) 
{
	int i, m, k;		// INDEXS // i -> json token index  ||  m -> sensor index  ||  k -> value index
  	
  	///// Init jsmn parse json library /////
  	jsmn_parser p;
  	jsmntok_t tokens[128];
  	jsmn_init(&p);
  	jsmn_parse(&p, js, strlen(js), tokens, 128);  
	jsmntok_t *token;
	i = 0;

	token = tokens + i;
	
	///// Start to parse /////
	// IOT2TANGLE HEADER
	while (token->type != JSMN_STRING) { token = tokens + ++i; }	// search the next string in the json
	// useless "message" string
	do{token = tokens + ++i;} while(token->type != JSMN_PRIMITIVE);	// search the next primitive (int, float or boolean) in the json
	
	j->id_keepy = recover_int(js, token->start, token->end);
	
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	// useless "message" string
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	
	sprintf(j->credential, recover_str(js, token->start, token->end));		//'iot2tangle' header string
	if ( strcmp(j->credential, "iot2tangle") != 0 )
		return false;
	
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	
	m = 0;
	// SENSORS
	while ( strcmp(recover_str(js, token->start, token->end), "sensor") == 0 )
	{
		k = 0;
		
		j->sensor[m].isEnable = true;		// Enable this Sensor index
				
		do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
					
		sprintf(j->sensor[m].id, recover_str(js, token->start, token->end));	// 'id sensor' string
					
		do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
		// useless "data" string
		do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
		
		while(1) 
		{
			char* aux = recover_str(js, token->start, token->end);
			if ( strcmp(aux,"sensor") == 0 || strcmp(aux,"device") == 0 )	// check if we have finished reading sensor values
				break;
			
			sprintf(j->sensor[m].name[k], recover_str(js, token->start, token->end));	// 'name of the value' string

			do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
					
			sprintf(j->sensor[m].value[k], recover_str(js, token->start, token->end));	// 'value' string
			
			do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
			
			k++;		
		}
		j->sensor[m].num_values = k;		// Save the numbers of Sensor Values
  		
  		m++;
  	}
	
	// DEVICE
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	
	sprintf(j->id, recover_str(js, token->start, token->end));	 	// 'ID Device' string
  	
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	// useless "timestamp" string	
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	
	char s_aux[10];
	sprintf(s_aux, recover_str(js, token->start, token->end));
	j->timestamp = atoi(s_aux);										// 'timestamp' long int
	
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	// useless "channel" string
	do{token = tokens + ++i;} while(token->type != JSMN_STRING);	// search the next string in the json
	
	sprintf(j->channel, recover_str(js, token->start, token->end));	// 'channel' string
	
	for (int z = m; z < MAX_SENSORS; z++) j->sensor[z].isEnable = false;	// Disable the rest of the sensors

   	return true;
}

char* recover_str(const char* j, int init_char, int final_char)	// Function for recover string from the json
{
	int i;
	char buffer[100];
	char* s = " ";
	for (i=0; i < final_char - init_char; i++)
	{
		buffer[i] = j[init_char+i];
	}
	buffer[i] = '\0'; // End of string
	s = buffer;
	printf (" ");
	return s;
}

int recover_int(const char* j, int init_char, int final_char)	// Function for recover string from the json
{
	int i, value;
	char buffer[100];
	for (i=0; i < final_char - init_char; i++)
	{
		buffer[i] = j[init_char+i];
	}
	buffer[i] = '\0'; // End of string
	value = atoi(buffer);
	return value;
}
