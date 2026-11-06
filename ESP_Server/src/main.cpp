//INI ESP32 YANG BARU
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <esp_err.h>
#include <ArduinoJson.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "LittleFS.h"
#include "class.h"
#include "espnow.h"

#define EEPROM_SIZE 512
#define CHANNEL 6
#define buzzer 14

//servo-servo
//SERVO KAKI KIRI
#define KAKI_KIRI_YAW 34
#define KAKI_KIRI_PITCH 35
#define LUTUT_KIRI 33
#define TELAPAK_KIRI 25

//SERVO KAKI KANAN
#define KAKI_KANAN_YAW 27
#define KAKI_KANAN_PITCH 14
#define LUTUT_KANAN 12
#define TELAPAK_KANAN 13

//SERVO TANGAN KIRI
#define TANGAN_KIRI_PITCH 23
#define TANGAN_KIRI_ROLL 22
#define SIKU_KIRI 21

//SERVO TANGAN KANAN
#define TANGAN_KANAN_PITCH 19
#define TANGAN_KANAN_ROLL 18
#define SIKU_KANAN 17

void setup() {
 Serial.begin(115200);
 
  Serial.println("Transmitter Init...");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(2000);
  Serial.println("Buzzer Menyala");
  digitalWrite(buzzer, HIGH);
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

  if(!LittleFS.begin(true)){
    Serial.println("Little FS failed");
    return;
  }else{
    Serial.println("LittleFS Success!");
  }

  Serial.println("Siap.");
  digitalWrite(buzzer,LOW);
}

void loop() {
  
}