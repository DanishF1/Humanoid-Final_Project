#ifndef espnow_h
#define espnow_h
//ESPNOW
extern String inputSerial;

uint8_t mac_addresses[1][6] = {
    {0x20,0x9B,0xA9,0x97,0x79,0x90}  // ESP 32 SERVER
};
esp_now_peer_info_t peerInfo;
struct data{
  char pesan[250];
};
data dataTerima;
data dataKirim;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  digitalWrite(LED_BUILTIN, status == ESP_NOW_SEND_SUCCESS ? HIGH : LOW);
  if(status ==  ESP_NOW_SEND_SUCCESS){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Data berhasil dikirim " + inputSerial);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("ESPNOW gagal mengirim " + inputSerial);
  }
  delay(600);
  digitalWrite(LED_BUILTIN, LOW);
  
}


void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memset(&dataTerima, 0, sizeof(dataTerima));
  memcpy(dataTerima.pesan, incomingData, min(len, (int)sizeof(dataTerima.pesan) - 1));
  String pesan = dataTerima.pesan;
  String header = pesan.substring(0, 2);
  if(header == "FF"){
    Serial.println(pesan);
    
  }
  
}

#endif