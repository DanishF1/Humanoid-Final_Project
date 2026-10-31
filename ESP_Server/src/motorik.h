#pragma once
#include"LittleFS.h"
#include <Arduino.h>
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
        while(file.available()){
        deserializeJson(doc, file);
        int total_actuators = doc["total_actuators"];
        int total_frames = doc["total_frames"];
        int total_times = doc["total_times"];
        int times[total_times] = {doc["times"]};
        int frames[total_actuators][total_frames] = {doc["frames"]}; 
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
