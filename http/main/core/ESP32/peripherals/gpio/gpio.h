#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdbool.h>

void init_LEDs();
void led_GPIO(int, int);
bool read_GPIO(int);

#endif
