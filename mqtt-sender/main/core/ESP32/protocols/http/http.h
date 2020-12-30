#ifndef _HTTP_H_
#define _HTTP_H_

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_tls.h"

#include "esp_http_client.h"

esp_err_t _http_event_handler(esp_http_client_event_t*);
bool init_socket(const char*, int, const char*, const char*, bool);
bool socket_sender(const char*, int, const char*, const char*, const char*, const char*, long);

#endif


