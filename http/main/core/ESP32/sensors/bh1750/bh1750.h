#ifndef _BH1750_H_
#define _BH1750_H_

#include <stdbool.h>

bool check_bh1750(void);
void init_bh1750(bool);
char* get_bh1750(void);
void print_bh1750(void);

#endif
