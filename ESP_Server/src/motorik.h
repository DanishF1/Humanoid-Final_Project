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
int interpolation(int sudutAkhir, int waktuBerjalan, int waktuTarget){
    if(waktuBerjalan == waktuTarget){
        return sudutAkhir;
    }else{
        float progress = (float)waktuBerjalan/waktuTarget;
        int sudutInterpolasi = 45 + (sudutAkhir - 45) * progress;
        return sudutInterpolasi;
    }
}

void kakiKananMaju(){
    if(LittleFS.exists("data/maju.json")){
        file = LittleFS.open("data/maju.json");
    }
        int timeNow = millis();
        while(file.available()){
        deserializeJson(doc, file);
        int total_frames = doc["total_frames"];
        int total_times = doc["total_times"];
        int times[total_times] = {doc["times"]};
        int frames[total_frames][14] = {doc["frames"]}; 
        int rows = sizeof(frames)/sizeof(frames[0]);
        int cols = sizeof(frames[0])/sizeof(frames[0][0]);
        int timeSize = sizeof(times)/sizeof(times[0]);

        for (int i=0; i<timeSize;i++){
            // TANGAN KANAN
            int desiredTanganKananRoll  = frames[i][0];
            int desiredTanganKananPitch = frames[i][1];
            int desiredSikuKanan        = frames[i][2];

            // TANGAN KIRI
            int desiredTanganKiriRoll   = frames[i][3];
            int desiredTanganKiriPitch  = frames[i][4];
            int desiredSikuKiri         = frames[i][5];

            // KAKI KANAN
            int desiredKakiKananYaw     = frames[i][6];
            int desiredKakiKananPitch   = frames[i][7];
            int desiredLututKanan       = frames[i][8];
            int desiredTelapakKanan     = frames[i][9];

            // KAKI KIRI
            int desiredKakiKiriYaw      = frames[i][10];
            int desiredKakiKiriPitch    = frames[i][11];
            int desiredLututKiri        = frames[i][12];
            int desiredTelapakKiri      = frames[i][13];

            // Tangan Kanan
            //NANTI KUBENERIN
            servoTanganKananRoll.write(interpolation(desiredTanganKananRoll, timeNow, times[i]));
            servoTanganKananPitch.write(desiredTanganKananPitch);
            servoSikuKanan.write(desiredSikuKanan);

            // Tangan Kiri
            servoTanganKiriRoll.write(desiredTanganKiriRoll);
            servoTanganKiriPitch.write(desiredTanganKiriPitch);
            servoSikuKiri.write(desiredSikuKiri);

            // Kaki Kanan
            servoKakiKananYaw.write(desiredKakiKananYaw);
            servoKakiKananPitch.write(desiredKakiKananPitch);
            servoLututKanan.write(desiredLututKanan);
            servoTelapakKanan.write(desiredTelapakKanan);

            // Kaki Kiri
            servoKakiKiriYaw.write(desiredKakiKiriYaw);
            servoKakiKiriPitch.write(desiredKakiKiriPitch);
            servoLututKiri.write(desiredLututKiri);
            servoTelapakKiri.write(desiredTelapakKiri);

        }
        }

        
}

void kakiKiriMaju(){

}

void kakiKananMundur(){

}

void kakiKiriMundur(){

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

class joget{
  //to be continued...
};
