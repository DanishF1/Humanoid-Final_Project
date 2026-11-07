#pragma once
#include"LittleFS.h"
#include <Arduino.h>
#include <ESP32Servo.h>

extern Servo servoKakiKiriYaw;
extern Servo servoKakiKiriPitch;
extern Servo servoLututKiri;
extern Servo servoTelapakKiri;

extern Servo servoKakiKananYaw;
extern Servo servoKakiKananPitch;
extern Servo servoLututKanan;
extern Servo servoTelapakKanan;

extern Servo servoTanganKiriPitch;
extern Servo servoTanganKiriRoll;
extern Servo servoSikuKiri;

extern Servo servoTanganKananPitch;
extern Servo servoTanganKananRoll;
extern Servo servoSikuKanan;

enum state{
IDLE, 
MAJU,
MUNDUR,
KANAN,
KIRI,
JOGET
};
File file;
JsonDocument doc;
state currentState = IDLE;

class rawMotorik{
    public:

int interpolation(int sudutAwal, int sudutAkhir, int waktuBerjalan, int waktuTarget){
    if(waktuBerjalan == waktuTarget){
        return sudutAkhir;
    }else{
        float progress = (float)waktuBerjalan/waktuTarget;
        float easeProgress = (1.0f - cos(progress * PI)) / 2.0f;
        int sudutInterpolasi = sudutAwal + (sudutAkhir - sudutAwal) * easeProgress;
        return sudutInterpolasi;
    }
}

void kakiKananMaju(){
    if(LittleFS.exists("/majuKakiKanan.json")){
        file = LittleFS.open("/majuKakiKanan.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        int total_frames = doc["total_frames"];
        int total_times = doc["total_times"];
        int times[total_times] = {doc["times"]};
        int frames[total_frames][14] = {doc["frames"]}; 
        int timeSize = sizeof(times)/sizeof(times[0]);

        for (int i=0; i<timeSize;i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            unsigned long timeNows = millis();
            int sudutAwal[14] = {
            servoTanganKananRoll.read(),  servoTanganKananPitch.read(), servoSikuKanan.read(),
            servoTanganKiriRoll.read(),   servoTanganKiriPitch.read(),  servoSikuKiri.read(),
            servoKakiKananYaw.read(),     servoKakiKananPitch.read(),   servoLututKanan.read(), servoTelapakKanan.read(),
            servoKakiKiriYaw.read(),      servoKakiKiriPitch.read(),    servoLututKiri.read(),  servoTelapakKiri.read()
            };
            while(true){
            unsigned long timeBerjalan = millis() - timeNows;
            
            // Tangan Kanan
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, times[i]));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, times[i]));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, times[i]));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, times[i]));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, times[i]));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, times[i]));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, times[i])); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, times[i]));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, times[i]));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, times[i]));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, times[i]));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, times[i]));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, times[i]));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, times[i]));

            delay(15);
            if(timeBerjalan >= times[i]) break;
        }

        }
        }

        
}

void kakiKiriMaju(){
if(LittleFS.exists("/majuKakiKiri.json")){
        file = LittleFS.open("/majuKakiKiri.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        int total_frames = doc["total_frames"];
        int total_times = doc["total_times"];
        int times[total_times] = {doc["times"]};
        int frames[total_frames][14] = {doc["frames"]}; 
        int timeSize = sizeof(times)/sizeof(times[0]);

        for (int i=0; i<timeSize;i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            unsigned long timeNows = millis();
            int sudutAwal[14] = {
            servoTanganKananRoll.read(),  servoTanganKananPitch.read(), servoSikuKanan.read(),
            servoTanganKiriRoll.read(),   servoTanganKiriPitch.read(),  servoSikuKiri.read(),
            servoKakiKananYaw.read(),     servoKakiKananPitch.read(),   servoLututKanan.read(), servoTelapakKanan.read(),
            servoKakiKiriYaw.read(),      servoKakiKiriPitch.read(),    servoLututKiri.read(),  servoTelapakKiri.read()
            };
            while(true){
            unsigned long timeBerjalan = millis() - timeNows;
            
            // Tangan Kanan
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, times[i]));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, times[i]));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, times[i]));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, times[i]));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, times[i]));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, times[i]));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, times[i])); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, times[i]));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, times[i]));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, times[i]));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, times[i]));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, times[i]));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, times[i]));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, times[i]));

            delay(15);
            if(timeBerjalan >= times[i]) break;
        }

        }
        }
}

void kakiKananMundur(){
    if(LittleFS.exists("/mundurKakiKanan.json")){
            file = LittleFS.open("/mundurKakiKanan.json");
        }
            while(file.available()){
            deserializeJson(doc, file);
            int total_frames = doc["total_frames"];
            int total_times = doc["total_times"];
            int times[total_times] = {doc["times"]};
            int frames[total_frames][14] = {doc["frames"]}; 
            int timeSize = sizeof(times)/sizeof(times[0]);

            for (int i=0; i<timeSize;i++){
                Serial.println("Sekarang frame ke- ");
                Serial.print(i);
                unsigned long timeNows = millis();
                int sudutAwal[14] = {
                servoTanganKananRoll.read(),  servoTanganKananPitch.read(), servoSikuKanan.read(),
                servoTanganKiriRoll.read(),   servoTanganKiriPitch.read(),  servoSikuKiri.read(),
                servoKakiKananYaw.read(),     servoKakiKananPitch.read(),   servoLututKanan.read(), servoTelapakKanan.read(),
                servoKakiKiriYaw.read(),      servoKakiKiriPitch.read(),    servoLututKiri.read(),  servoTelapakKiri.read()
                };
                while(true){
                unsigned long timeBerjalan = millis() - timeNows;
                
                // Tangan Kanan
                servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, times[i]));
                servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, times[i]));
                servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, times[i]));

                // Tangan Kiri
                servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, times[i]));
                servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, times[i]));
                servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, times[i]));

                // Kaki Kanan
                servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, times[i])); 
                servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, times[i]));
                servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, times[i]));
                servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, times[i]));

                // Kaki Kiri
                servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, times[i]));
                servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, times[i]));
                servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, times[i]));
                servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, times[i]));

                delay(15);
                if(timeBerjalan >= times[i]) break;
            }

            }
            }
}

void kakiKiriMundur(){
if(LittleFS.exists("/mundurKakiKiri.json")){
        file = LittleFS.open("/mundurKakiKiri.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        int total_frames = doc["total_frames"];
        int total_times = doc["total_times"];
        int times[total_times] = {doc["times"]};
        int frames[total_frames][14] = {doc["frames"]}; 
        int timeSize = sizeof(times)/sizeof(times[0]);

        for (int i=0; i<timeSize;i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            unsigned long timeNows = millis();
            int sudutAwal[14] = {
            servoTanganKananRoll.read(),  servoTanganKananPitch.read(), servoSikuKanan.read(),
            servoTanganKiriRoll.read(),   servoTanganKiriPitch.read(),  servoSikuKiri.read(),
            servoKakiKananYaw.read(),     servoKakiKananPitch.read(),   servoLututKanan.read(), servoTelapakKanan.read(),
            servoKakiKiriYaw.read(),      servoKakiKiriPitch.read(),    servoLututKiri.read(),  servoTelapakKiri.read()
            };
            while(true){
            unsigned long timeBerjalan = millis() - timeNows;
            
            // Tangan Kanan
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, times[i]));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, times[i]));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, times[i]));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, times[i]));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, times[i]));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, times[i]));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, times[i])); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, times[i]));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, times[i]));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, times[i]));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, times[i]));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, times[i]));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, times[i]));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, times[i]));

            delay(15);
            if(timeBerjalan >= times[i]) break;
        }

        }
        }
}
};

class motorik{
    private:
    rawMotorik rm;
    public:
    bool isIdle(){
        if(currentState != IDLE) return false;
        return true;
    }

    motorik(){}
void maju(int timex){
    if(currentState != IDLE) return;
    currentState = MAJU;
    Serial.println("MAJU");


for(int i =0;i<timex;i++){
    if(i==0 || i%2 == 0){
        rm.kakiKananMaju();
    }else{
        rm.kakiKiriMaju();
    }
    
}
    currentState = IDLE;
}

void mundur(int timex){
    if(currentState != IDLE) return;
    currentState = MUNDUR;
for(int i =0;i<timex;i++){
    if(i==0 || i%2 == 0){
        rm.kakiKiriMundur();
    }else{
        rm.kakiKananMundur();
    }
}
    currentState = IDLE;
}
void belokKanan(int timex){
    if(currentState != IDLE) return;
    currentState = KANAN;

    currentState = IDLE;
}

void belokKiri(int timex){
    if(currentState != IDLE) return;
    currentState = MAJU;

    currentState = IDLE;
}

~motorik(){
}
};

class boxing{
  //to be continued...
};
