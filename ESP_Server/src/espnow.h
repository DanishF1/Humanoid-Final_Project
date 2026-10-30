#ifndef espnow_h
#define espnow_h
#include "class.h"
//ESPNOW
#define led 2
#include <ArduinoJson.h>
#include "motorik.h"
int nomorAntrean = 0;
int address = 0;        
int addressTime = 1;    
String payloadEN;
uint8_t mac_addresses[1][6] = {
    {0x08,0xA6,0xF7,0xBD,0x45,0x60}  // ESP 32 SERVER
};
esp_now_peer_info_t peerInfo;
struct data{
  char pesan[250];
  int id;
};
data dataTerima;
data dataKirim;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  sendToBridge s;
  Serial.println("MENGIRIM");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SEND OK" : "SEND FAIL");
}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  sendToBridge s;
  motorik m;
  payloadEN = dataTerima.pesan;
  Serial.println("DATA DITERIMA");
  Serial.println(dataTerima.pesan);
  memset(&dataTerima, 0, sizeof(dataTerima));                                      
  memcpy(&dataTerima, incomingData, min(len, (int)sizeof(dataTerima.pesan) - 1));    

  String pesan = dataTerima.pesan;
  if(pesan.length() < 2) return;    
  String header = pesan.substring(0, 2);
  String leng;
  int lengInt;
  
  if(header == "FF"){
  Serial.println("INPUT VALID");
  if(pesan.length() == 5){
    //FFw01
    char cmd;
    leng = pesan.substring(3,5);
    lengInt = leng.toInt();
    cmd = pesan[2];
    switch(cmd){
      case 'w':
      m.maju(lengInt);
      break;
      case 's':
      m.mundur(lengInt);
      break;
      case 'd':
      m.belokKanan(lengInt);
      break;
      case 'a':
      m.belokKiri(lengInt);
      break;
      default:
       break;
    }
  }else if(pesan.length() == 6){
    //buat kalo joget
    String cmd;
    leng = pesan.substring(4,6);
    lengInt = leng.toInt();
    cmd = pesan.substring(2,4);
  }

  }
}

#endif