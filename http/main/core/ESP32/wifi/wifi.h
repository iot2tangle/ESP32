#ifndef _WIFI_H_
#define _WIFI_H_
#include <stdbool.h>

#include "esp_wifi.h"

esp_err_t event_handler(void *ctx, system_event_t *event);
bool connectAttempt(const char*,const char*);

#endif
