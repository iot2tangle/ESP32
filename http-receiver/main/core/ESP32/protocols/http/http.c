#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "http.h"
#include "esp_http_client.h"

#define MAX_HTTP_RECV_BUFFER 1024

static const char *TAG = "HTTP_CLIENT";
esp_http_client_handle_t client;

bool get_json(char* js, const char* endp, int p, const char* _top, const char* _us, const char* _pass, long _t)
{

	// URL adaptation
    char* p_s = " ";
    char p_buff[8];
    sprintf(p_buff, ":%d/", p);
    p_s = p_buff;
    
    const char* u = " ";
    char s_buffer[40], aux[40];
    strcpy(aux, endp);
    
    char* c_aux;
    c_aux = strtok(aux, "/");
    strcpy(s_buffer, "http://");
    strcat(s_buffer, c_aux);
    strcat(s_buffer, p_s);
    c_aux = strtok(NULL, "\0");
    strcat(s_buffer, c_aux);
    u=s_buffer;

	// GET
    char *buffer = malloc(MAX_HTTP_RECV_BUFFER + 1);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Cannot malloc http receive buffer");
        return false;
    }
    esp_http_client_config_t config = {
        .url = u,
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err;
    if ((err = esp_http_client_open(client, 0)) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        free(buffer);
        return false;
    }
    int content_length =  esp_http_client_fetch_headers(client);
    int total_read_len = 0, read_len;
    if (total_read_len < content_length && content_length <= MAX_HTTP_RECV_BUFFER) {
        read_len = esp_http_client_read(client, buffer, content_length);
        if (read_len <= 0) {
            ESP_LOGE(TAG, "Error read data");
        }
        buffer[read_len] = 0;
        ESP_LOGD(TAG, "read_len = %d", read_len);
    }
    ESP_LOGI(TAG, "HTTP Stream reader Status = %d, content_length = %d",
                    esp_http_client_get_status_code(client),
                    esp_http_client_get_content_length(client));
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    
	strcpy(js, buffer);
    free(buffer);
    
    return true;
}

bool init_socket(const char* endp, int p, const char* _us, const char* _pass, bool ft_http)
{
    if (ft_http == true)
    {
		// URL adaptation
		char* p_s = " ";
		char p_buff[8];
		sprintf(p_buff, ":%d/", p);
		p_s = p_buff;
		
		const char* u = " ";
		char buffer[40], aux[40];
		strcpy(aux, endp);
		
		char* c_aux;
		c_aux = strtok(aux, "/");
		strcpy(buffer, "http://");
		strcat(buffer, c_aux);
		strcat(buffer, p_s);
		c_aux = strtok(NULL, "\0");
		strcat(buffer, c_aux);
		u=buffer;
		esp_err_t err; 
		
		esp_http_client_config_t config = {
		    .url = u,
		    .event_handler = _http_event_handler,
		};

    	client = esp_http_client_init(&config);
	
		err = esp_http_client_perform(client);

		if (err == 0)
		{
			printf(" -- The Configuration Network is correct, getting data from The Tangle --\n");
			esp_http_client_cleanup(client);
			return true; 
		}
		else
		{
			printf(" -- Endpoint is NOT detected!! -- Please, check your configuration --\n");
			esp_http_client_cleanup(client);
			return false;
		}
    }
    /* No need to reconnect on ESP32 */
    return true;
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                // printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error(evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            break;
	}
    return ESP_OK;
}
