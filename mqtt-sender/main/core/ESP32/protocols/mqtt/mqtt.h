#include "stdint.h"
#include "esp_event_base.h"
#include "mqtt_client.h"


#ifndef _MQTT_H_
#define _MQTT_H_


#include "esp_err.h"
#include "stdbool.h"

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event);
bool init_socket(const char * addr, int port, const char * user_mqtt, const char * user_pswd, bool b);
bool socket_sender(const char *, int, const char *, const char *, const char *, const char *, long);

#endif