#include <stdio.h>

#include "esp_netif.h"

int gethostname(char *name, size_t len) {
  esp_netif_t *netif = NULL;
  esp_netif_ip_info_t ip;
  int i = esp_netif_get_nr_of_ifs();
  if (i == 1) {
    netif = esp_netif_next(netif);
    ESP_ERROR_CHECK(esp_netif_get_ip_info(netif, &ip));
    snprintf(name, len, IPSTR, IP2STR(&ip.ip));
  } else {
    snprintf(name, len, "esp32");
  }
  return 0;
}
