//INI ESP32 YANG BARU
#include <Arduino.h>
#include <WiFi.h>
#include <esp_err.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include "class.h"
#include "espnow.h"
#include "tone.h"
#include "esp_random.h"

long long timeSetup;
long long timeLoop;
int fMaks = 4000;
int fMin = 1000;
const int CHANNEL = 6;
const int buzzer = 16;

//servo-servo
//SERVO KAKI KIRI
const int KAKI_KIRI_YAW = 32;
const int KAKI_KIRI_PITCH = 33;
const int LUTUT_KIRI = 25;
const int TELAPAK_KIRI = 27;

//SERVO KAKI KANAN
const int KAKI_KANAN_YAW = 13;
const int KAKI_KANAN_PITCH = 12;
const int LUTUT_KANAN = 14;
const int TELAPAK_KANAN = 26;

//SERVO TANGAN KIRI
const int TANGAN_KIRI_PITCH = 23;
const int TANGAN_KIRI_ROLL = 22;
const int SIKU_KIRI = 21;

//SERVO TANGAN KANAN
const int TANGAN_KANAN_PITCH = 17;
const int TANGAN_KANAN_ROLL = 18;
const int SIKU_KANAN = 19;

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

  tone(buzzer, fMaks);
  unsigned long waktuMulai = millis();

  while (millis() - waktuMulai < 500) {

  }
 tone(buzzer, fMin);
   while (millis() - waktuMulai < 1000) {

  }
  tone(buzzer, fMaks);
   while (millis() - waktuMulai < 1500) {

  }
  tone(buzzer, fMin);
   while (millis() - waktuMulai < 2000) {

  }

  /*int random = esp_random();
  if(random % 2 == 0 || random == 0){
    buzz1();
  }else{
    buzz();
  }*/
  noTone(buzzer);
  

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

    servoTanganKananRoll.write(0);    // 0
  servoTanganKananPitch.write(90);  // 1
  servoSikuKanan.write(0);          // 2
  servoTanganKiriRoll.write(180);     // 3
  servoTanganKiriPitch.write(90);   // 4
  servoSikuKiri.write(180);           // 5
  servoKakiKananYaw.write(90);      // 6
  servoKakiKananPitch.write(90);    // 7
  servoLututKanan.write(180);         // 8
  servoTelapakKanan.write(90);      // 9
  servoKakiKiriYaw.write(90);       // 10
  servoKakiKiriPitch.write(90);     // 11
  servoLututKiri.write(0);          // 12
  servoTelapakKiri.write(90);       // 13

}

void loop() {
 
}