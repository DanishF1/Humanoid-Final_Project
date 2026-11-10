#ifndef espnow_h
#define espnow_h
#include "class.h"
//ESPNOW
#define led 2
#include <ArduinoJson.h>
#include "motorik.h"
extern const int buzzer;
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

}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  sendToBridge s;
  motorik m;
  boxing b;
  payloadEN = dataTerima.pesan;
  memset(&dataTerima, 0, sizeof(dataTerima));                                      
  memcpy(&dataTerima, incomingData, min(len, (int)sizeof(dataTerima.pesan) - 1));    

  String pesan = dataTerima.pesan;
  if(pesan.length() < 2) return;    
  String header = pesan.substring(0, 2);
  String leng;
  int lengInt;
  unsigned long timeNow = millis();
  if(header == "FF"){
  if(pesan.length() == 5){
    char cmd;
    unsigned long waktuBerjalan =  millis() - timeNow;
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
      case 'f':
      b.fm(lengInt);
      case 'b':
      b.bc(lengInt);
      default:
       break;
    }
    if (waktuBerjalan <= 255){
      analogWrite(buzzer, waktuBerjalan-255);
    }else{
      digitalWrite(buzzer, LOW);
    }
  }else{
    return;
  }

  }
}

#endif