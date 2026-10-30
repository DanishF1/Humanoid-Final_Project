//INI ESP32 YANG BARU
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <ArduinoJson.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "SPIFFS.h"

#include "class.h"
#include "espnow.h"

#define EEPROM_SIZE 512
#define CHANNEL 6

void setup() {
 Serial.begin(115200);
  Serial.println("Transmitter Init...");
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  esp_wifi_set_ps(WIFI_PS_NONE);

  WiFi.mode(WIFI_STA);

  esp_err_t power = esp_wifi_set_max_tx_power(78);
    if (power == ESP_OK) {
        Serial.println("TX Power berhasil diatur ke 19.5 dBm");
    }else{
      Serial.println("gagal power");
    }

  esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(CHANNEL, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);

  Serial.print("MAC ESP lama: ");
  Serial.println(WiFi.macAddress());


  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init gagal");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);

  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, mac_addresses[0], 6);
  peerInfo.channel = 0;     
  peerInfo.encrypt = false;

  esp_err_t err = esp_now_add_peer(&peerInfo);
  if (err != ESP_OK) {
    Serial.print("Gagal add peer: ");
    Serial.println(esp_err_to_name(err));
    return;
  }
  Serial.println("Siap.");
}

void loop() {
  
}