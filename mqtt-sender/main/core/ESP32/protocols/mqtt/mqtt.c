#include "mqtt.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "esp_err.h"
#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "MQTT_CLIENT";

bool socket_sender(const char *endp, int p, const char *_top, const char *_us, const char *_pass, const char *j, long t)
{
    //ESP_LOGE(TAG, "socket_sender");
    char p_str[50];
    char address[100];
    sprintf(p_str, "%d", p);	/* Convert port to string */
	
	strcpy(address, "mqtt://");
    strcat(address, endp);


    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = address,
        .port = p,
        .username = _us,
        .password = _pass,
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_err_t error = esp_mqtt_client_start(client);
    ESP_LOGI(TAG, "MQTT Sender return: %s",esp_err_to_name(error));

    int msg_id;
    msg_id = esp_mqtt_client_subscribe(client, _top, 1);
    //ESP_LOGI(TAG, "resultado suscripcion_id:%d", msg_id);

    if (msg_id == -1)
    {
        printf(" -- Endpoint is NOT detected!! -- Please, check your configuration --\n");
        esp_mqtt_client_stop(client);
        return false;
    }
    else
	{
	//	printf("Suscrito correctamente a topico\n");

		msg_id = esp_mqtt_client_publish(client, _top, j, 0, 1, 0);

		printf("		-- Data Published in the Broker! -- \n\n");
		esp_mqtt_client_stop(client);
		return true;
	}
}

bool init_socket(const char *endp, int p, const char *_us, const char *_pass, bool ft_http)
{
    ESP_LOGI(TAG, "init MQTT socket...");
    if (ft_http == true)
    {
        char p_str[50];
        char address[100];

        sprintf(p_str, "%d", p);	/* Convert port to string */
	
	strcpy(address, "mqtt://");
    strcat(address, endp);

        esp_mqtt_client_config_t mqtt_cfg = {
            .uri = address,
            .port = p,
            .username = _us,
            .password = _pass,
        };

        esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
        esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
        esp_err_t error = esp_mqtt_client_start(client);
        ESP_LOGI(TAG, "MQTT Sender return: %s",esp_err_to_name(error));

        int msg_id;
        msg_id = esp_mqtt_client_subscribe(client, "/topic/raaa", 1);

        if (msg_id == -1)
        {
            printf(" -- MQTT Broker is NOT detected!! -- Please, check your configuration --\nRebooting....");
            esp_mqtt_client_stop(client);
            return false;
        }
        else
        {
            printf(" -- The MQTT Configuration Network is correct, sending data to The Tangle --\n");
            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/raaa");
            esp_mqtt_client_stop(client);
            return true;
        }
    }
    /* No need to reconnect on ESP32 */
    return true;
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    switch (event->event_id)
    {
		case MQTT_EVENT_CONNECTED:
		    ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
		    break;
		case MQTT_EVENT_DISCONNECTED:
		    ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
		    break;
		case MQTT_EVENT_SUBSCRIBED:
		    ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
		    break;
		case MQTT_EVENT_UNSUBSCRIBED:
		    ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
		    break;
		case MQTT_EVENT_PUBLISHED:
		    ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
		    break;
		case MQTT_EVENT_DATA:
		    ESP_LOGI(TAG, "MQTT_EVENT_DATA");
		    printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
		    printf("DATA=%.*s\r\n", event->data_len, event->data);
		    break;
		case MQTT_EVENT_ERROR:
		    ESP_LOGE(TAG, "MQTT_EVENT_ERROR");
		    break;
		default:
		    break;
    }
    return ESP_OK;
}
