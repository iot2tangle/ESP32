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
  	int r = jsmn_parse(&p, js, strlen(js), tokens, 128);  
  	//printf("Amount of Tokens of the json: %d\n", r);
	jsmntok_t *token;
	i = 0;
	m = 0;
	token = tokens + i;
	
	///// Start to parse /////
	// IOT2TANGLE HEADER
	while (token->type != JSMN_STRING) { token = tokens + ++i; } 	
	
	sprintf(j->credential, recover_str(js, token->start, token->end));		//"iot2tangle" header string
	if ( strcmp(j->credential, "iot2tangle") != 0 )
		return false;
	
  	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; } 	
	
	// SENSORS
	while ( strcmp(recover_str(js, token->start, token->end), "sensor") == 0 )
	{
		k = 0;
		token = tokens + ++i;
		while (token->type != JSMN_STRING) { token = tokens + ++i; } 
					
		sprintf(j->sensor[m].id, recover_str(js, token->start, token->end));	// id sensor string
					
		token = tokens + ++i;
		while (token->type != JSMN_STRING) { token = tokens + ++i; }
		// useless "data" string
		token = tokens + ++i;
		while (token->type != JSMN_STRING) { token = tokens + ++i; }
		
		while(1)
		{
			char* aux = recover_str(js, token->start, token->end);
			if ( strcmp(aux,"sensor") == 0 || strcmp(aux,"device") == 0 )	// check if we have finished reading sensor values
				break;
			
			sprintf(j->sensor[m].name[k], recover_str(js, token->start, token->end));	// name of the value string

			token = tokens + ++i;
			while (token->type != JSMN_STRING) { token = tokens + ++i; }
					
			sprintf(j->sensor[m].value[k], recover_str(js, token->start, token->end));	// value string
			
			token = tokens + ++i;
			while (token->type != JSMN_STRING) { token = tokens + ++i; }
			
			k++;		
		}
  		m++;
  	}
	
	// DEVICE
  	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; }
	
	sprintf(j->id, recover_str(js, token->start, token->end));	 	// ID Device string
  	
  	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; }
	// useless "timestamp" string
	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; }
	
	j->timestamp = atoi(recover_str(js, token->start, token->end));	// Timestamp string
	
	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; }
	// useless "relative_timestamp" string
	token = tokens + ++i;
	while (token->type != JSMN_STRING) { token = tokens + ++i; }
	
	j->relative_timestamp = atoi(recover_str(js, token->start, token->end));	// Timestamp string

   	return true;
}

char* recover_str(const char* j, int init_char, int final_char)
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
