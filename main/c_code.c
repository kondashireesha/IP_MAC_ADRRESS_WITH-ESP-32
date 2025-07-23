#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#define WIFI_SSID "Your_SSID"//add user  name of the wi-fi 
#define WIFI_PASS "Your_PASSWORD"// add you wi-fi credentials here

static const char *TAG = "WiFi_Info";

// Function to print MAC and IP once connected
void print_mac_ip_info()
{
    wifi_ap_record_t ap_info;
    if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK) {
        uint8_t mac[6];
        esp_wifi_get_mac(WIFI_IF_STA, mac);

        ESP_LOGI(TAG, "Connected to SSID: %s", (char *)ap_info.ssid);
        ESP_LOGI(TAG, "MAC Address: %02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);//mac adrres is 6bytes
    }
}
// Event handler when Wi-Fi state changes
static void wifi_event_handler(void *arg, esp_event_base_t event_base,
    int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "IP Address: " IPSTR, IP2STR(&event->ip_info.ip));
        print_mac_ip_info(); // Print MAC after getting IP
    }
}

// Initialize and connect to Wi-Fi
void wifi_connect()
{
    // Create default Wi-Fi station
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    // Wi-Fi init config
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    // Register event handlers
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);
    // Set Wi-Fi config
    wifi_config_t wifi_config = { 0 };
    strcpy((char *)wifi_config.sta.ssid, WIFI_SSID);
    strcpy((char *)wifi_config.sta.password, WIFI_PASS);
    // Start Wi-Fi in station mode
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    ESP_LOGI(TAG, "Connecting to Wi-Fi...");
}
void app_main()
{
    // Initialize NVS (required before Wi-Fi)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    ESP_LOGI(TAG, "ESP32 Wi-Fi MAC and IP Printer");
    wifi_connect();
}
