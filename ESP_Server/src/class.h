#ifndef class_h
#define class_h
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "motorik.h"
#include <esp_err.h>
extern int nomorAntrean;
extern uint8_t mac_addresses[1][6];
extern int address;
extern int addressTime;
extern String jamskr;
JsonDocument j;
extern String payloadEN;  

class spiffs{
spiffs(){}

~spiffs(){}
};

class sendToBridge{
public:
JsonDocument j;
sendToBridge(){}

void payloading(String message){
  int len = message.length();
  String leng;
  if(len>9 && len<100){
    leng = String(len);
  }else if(len>0 && len<10){
    leng = "0"+String(len);
  }else{
    leng = "00";
  }
  String payload = "FF";
  send(payload);   
}

void send(String message){

  esp_err_t result = esp_now_send(mac_addresses[0], (uint8_t*)message.c_str(), message.length());  
  if(result != ESP_OK){
    message = "E12";
    Serial.println(esp_err_to_name(result));   
    esp_err_t result = esp_now_send(mac_addresses[0], (uint8_t*)message.c_str(), message.length());  
  }

}

~sendToBridge(){}
};



#endif