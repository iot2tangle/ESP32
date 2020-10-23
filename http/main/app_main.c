#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "main.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/

void app_main(void)
{
    main();
	
    //vTaskStartScheduler();
}


