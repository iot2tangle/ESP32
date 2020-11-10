#ifndef _DECODER_I2T_JSON_H_
#define _DECODER_I2T_JSON_H_

#include <stdbool.h>

bool recover_json(char*, struct json *);
char* recover_str(const char*, int, int);
int recover_int(const char*, int, int);

#endif
