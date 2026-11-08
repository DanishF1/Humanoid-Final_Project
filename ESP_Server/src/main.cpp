//INI ESP32 YANG BARU
#include <Arduino.h>
#include <WiFi.h>
#include <esp_err.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "class.h"
#include "espnow.h"

const int CHANNEL = 6;
const int buzzer = 16;

//servo-servo
//SERVO KAKI KIRI
const int KAKI_KIRI_YAW = 32;
const int KAKI_KIRI_PITCH = 26;
const int LUTUT_KIRI = 33;
const int TELAPAK_KIRI = 25;

//SERVO KAKI KANAN
const int KAKI_KANAN_YAW = 27;
const int KAKI_KANAN_PITCH = 14;
const int LUTUT_KANAN = 12;
const int TELAPAK_KANAN = 13;

//SERVO TANGAN KIRI
const int TANGAN_KIRI_PITCH = 23;
const int TANGAN_KIRI_ROLL = 22;
const int SIKU_KIRI = 21;

//SERVO TANGAN KANAN
const int TANGAN_KANAN_PITCH = 19;
const int TANGAN_KANAN_ROLL = 18;
const int SIKU_KANAN = 17;

// Kaki Kiri
Servo servoKakiKiriYaw;
Servo servoKakiKiriPitch;
Servo servoLututKiri;
Servo servoTelapakKiri;

// Kaki Kanan
Servo servoKakiKananYaw;
Servo servoKakiKananPitch;
Servo servoLututKanan;
Servo servoTelapakKanan;

// Tangan Kiri
Servo servoTanganKiriPitch;
Servo servoTanganKiriRoll;
Servo servoSikuKiri;

// Tangan Kanan
Servo servoTanganKananPitch;
Servo servoTanganKananRoll;
Servo servoSikuKanan;

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

  WiFi.mode(WIFI_STA);

  esp_err_t power = esp_wifi_set_max_tx_power(35);
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

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Set Frekuensi standar servo (50Hz)
  servoKakiKiriYaw.setPeriodHertz(50);
  servoKakiKiriPitch.setPeriodHertz(50);
  servoLututKiri.setPeriodHertz(50);
  servoTelapakKiri.setPeriodHertz(50);

  servoKakiKananYaw.setPeriodHertz(50);
  servoKakiKananPitch.setPeriodHertz(50);
  servoLututKanan.setPeriodHertz(50);
  servoTelapakKanan.setPeriodHertz(50);

  servoTanganKiriPitch.setPeriodHertz(50);
  servoTanganKiriRoll.setPeriodHertz(50);
  servoSikuKiri.setPeriodHertz(50);

  servoTanganKananPitch.setPeriodHertz(50);
  servoTanganKananRoll.setPeriodHertz(50);
  servoSikuKanan.setPeriodHertz(50);

  // 4. ATTACH SERVO KE PIN PROSES (Pulse width standar: 500us - 2400us)
  // Kaki Kiri
  servoKakiKiriYaw.attach(KAKI_KIRI_YAW, 500, 2400);
  servoKakiKiriPitch.attach(KAKI_KIRI_PITCH, 500, 2400);
  servoLututKiri.attach(LUTUT_KIRI, 500, 2400);
  servoTelapakKiri.attach(TELAPAK_KIRI, 500, 2400);

  // Kaki Kanan
  servoKakiKananYaw.attach(KAKI_KANAN_YAW, 500, 2400);
  servoKakiKananPitch.attach(KAKI_KANAN_PITCH, 500, 2400);
  servoLututKanan.attach(LUTUT_KANAN, 500, 2400);
  servoTelapakKanan.attach(TELAPAK_KANAN, 500, 2400);

  // Tangan Kiri
  servoTanganKiriPitch.attach(TANGAN_KIRI_PITCH, 500, 2400);
  servoTanganKiriRoll.attach(TANGAN_KIRI_ROLL, 500, 2400);
  servoSikuKiri.attach(SIKU_KIRI, 500, 2400);

  // Tangan Kanan
  servoTanganKananPitch.attach(TANGAN_KANAN_PITCH, 500, 2400);
  servoTanganKananRoll.attach(TANGAN_KANAN_ROLL, 500, 2400);
  servoSikuKanan.attach(SIKU_KANAN, 500, 2400);

Servo* semua[14] = { &servoKakiKiriYaw, &servoKakiKiriPitch, &servoLututKiri, &servoTelapakKiri,
                     &servoKakiKananYaw, &servoKakiKananPitch, &servoLututKanan, &servoTelapakKanan,
                     &servoTanganKiriPitch, &servoTanganKiriRoll, &servoSikuKiri,
                     &servoTanganKananPitch, &servoTanganKananRoll, &servoSikuKanan };
int pin[14] = { KAKI_KIRI_YAW, KAKI_KIRI_PITCH, LUTUT_KIRI, TELAPAK_KIRI,
                KAKI_KANAN_YAW, KAKI_KANAN_PITCH, LUTUT_KANAN, TELAPAK_KANAN,
                TANGAN_KIRI_PITCH, TANGAN_KIRI_ROLL, SIKU_KIRI,
                TANGAN_KANAN_PITCH, TANGAN_KANAN_ROLL, SIKU_KANAN };

for(int k = 0; k < 14; k++){
  semua[k]->setPeriodHertz(50);
  semua[k]->attach(pin[k], 500, 2400);
  semua[k]->write(45);
  delay(300);   // beri waktu supply pulih sebelum servo berikutnya
}

  Serial.println("Siap.");
  digitalWrite(buzzer,LOW);
     delay(2000);
}

void loop() {
  
}