#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "http-socket.h"

int isEndpoint;

bool socket_sender(const char* endp, int p, const char* _top, const char* _us, const char* _pass, const char* j, long t)
{
    printf("			*** ");

    // SEND DATA TO ENDPOINT with return in isEndpoint about the success of the operation
    
    isEndpoint = 0; // 0 is Success in this example

    if (isEndpoint == 0)
    {
    		printf("Data Sucessfully sent to Tangle!\n");
		return true; 
    }
    else
    {
		if (isEndpoint==28)
		{
	        printf("Timeout! The data was sent to the Tangle, but no confirmation was received. It should still be included in Tangle.\nIf you receive this message very often you may need to increase the interval in seconds between data collection.\n");
	        return false;
		}
		else
		{
	        printf("Failed to send Data to Endpoint!\n");
	        return false;
		}
    }
}

bool isEndpointOk(const char* endp, int p, const char* _us, const char* _pass)
{
    
    // CHECK ENDPOINT
    
    isEndpoint = 0; // 0 is Success in this example
    
    if (isEndpoint == 0)
    {
	printf(" -- The Configuration Network is correct, sending data to The Tangle --\n");
	return true;
    }
    else
    {
	printf(" -- Endpoint is NOT detected!! -- Please, check your configuration --\n");
	return false;
    }
}
