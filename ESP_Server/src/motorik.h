#pragma once
#include"LittleFS.h"
#include <Arduino.h>
#include <ESP32Servo.h>

extern const int KAKI_KIRI_YAW;
extern const int KAKI_KIRI_PITCH;
extern const int LUTUT_KIRI;
extern const int TELAPAK_KIRI;

extern const int KAKI_KANAN_YAW;
extern const int KAKI_KANAN_PITCH;
extern const int LUTUT_KANAN;
extern const int TELAPAK_KANAN;

extern const int TANGAN_KIRI_PITCH;
extern const int TANGAN_KIRI_ROLL;
extern const int SIKU_KIRI;

extern const int TANGAN_KANAN_PITCH;
extern const int TANGAN_KANAN_ROLL;
extern const int SIKU_KANAN;
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
        for (int i=0; i<cols;i++){


            for (int j=0;j<rows;j++){

            }
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
