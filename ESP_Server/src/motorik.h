#pragma once
#include"LittleFS.h"
#include "tone.h"
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
int period = 1000;
unsigned long time_now = 0;
enum state{
IDLE, 
MAJU,
MUNDUR,
KANAN,
KIRI,
SPECIAL
};
File file;
JsonDocument doc;
state currentState = IDLE;

class rawMotorik{
    public:

int interpolation(int sudutAwal, int sudutAkhir, int waktuBerjalan, int waktuTarget){
    if(waktuBerjalan >= waktuTarget){
        return sudutAkhir;
    }else{
        float progress = (float)waktuBerjalan/waktuTarget;
        float easeProgress = (1.0f - cos(progress * PI)) / 2.0f;
        int sudutInterpolasi = sudutAwal + (sudutAkhir - sudutAwal) * easeProgress;
        return sudutInterpolasi;
    }
}

void stance(){
    if(LittleFS.exists("/stance.json")){
        file = LittleFS.open("/stance.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        int total = doc["total"];
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int tesSudut;
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

            delay(15);
            if(timeBerjalan >= durasiFrame) break;
        }

        }
        }
}
void kakiKananMaju(){
    if(LittleFS.exists("/majuKakiKanan.json")){
        file = LittleFS.open("/majuKakiKanan.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        int total = doc["total"];
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int tesSudut;
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

            delay(15);
            if(timeBerjalan >= durasiFrame) break;
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
        int total = doc["total"];
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));
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
            JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
                Serial.println("Sekarang frame ke- ");
                Serial.print(i);
                int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

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
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

            delay(15);
            if(timeBerjalan >= times[i]) break;
        }

        }
        }
}

    void bicepCurl(){
    if(LittleFS.exists("/bicepCurl.json")){
        file = LittleFS.open("/bicepCurl.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

            delay(15);
            if(timeBerjalan >= times[i]) break;
        }

        }
        }
}

        void flexMuscle(){
    if(LittleFS.exists("/flexMuscle.json")){
        file = LittleFS.open("/flexMuscle.json");
    }
        while(file.available()){
        deserializeJson(doc, file);
        JsonArray times  = doc["times"];
        JsonArray frames = doc["frames"];

        for (int i=0; i<times.size();i++){
            Serial.println("Sekarang frame ke- ");
            Serial.print(i);
            int t1  =times[i-1];
            int t2 = times [i];
                int durasiFrame = (i == 0) ? times[0] : (t2-t1);
    
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
            servoTanganKananRoll.write(interpolation(sudutAwal[0], frames[i][0], timeBerjalan, durasiFrame));
            servoTanganKananPitch.write(interpolation(sudutAwal[1], frames[i][1], timeBerjalan, durasiFrame));
            servoSikuKanan.write(interpolation(sudutAwal[2], frames[i][2], timeBerjalan, durasiFrame));

            // Tangan Kiri
            servoTanganKiriRoll.write(interpolation(sudutAwal[3], frames[i][3], timeBerjalan, durasiFrame));
            servoTanganKiriPitch.write(interpolation(sudutAwal[4], frames[i][4], timeBerjalan, durasiFrame));
            servoSikuKiri.write(interpolation(sudutAwal[5], frames[i][5], timeBerjalan, durasiFrame));

            // Kaki Kanan
            servoKakiKananYaw.write(interpolation(sudutAwal[6], frames[i][6], timeBerjalan, durasiFrame)); 
            servoKakiKananPitch.write(interpolation(sudutAwal[7], frames[i][7], timeBerjalan, durasiFrame));
            servoLututKanan.write(interpolation(sudutAwal[8], frames[i][8], timeBerjalan, durasiFrame));
            servoTelapakKanan.write(interpolation(sudutAwal[9], frames[i][9], timeBerjalan, durasiFrame));

            // Kaki Kiri
            servoKakiKiriYaw.write(interpolation(sudutAwal[10], frames[i][10], timeBerjalan, durasiFrame));
            servoKakiKiriPitch.write(interpolation(sudutAwal[11], frames[i][11], timeBerjalan, durasiFrame));
            servoLututKiri.write(interpolation(sudutAwal[12], frames[i][12], timeBerjalan, durasiFrame));
            servoTelapakKiri.write(interpolation(sudutAwal[13], frames[i][13], timeBerjalan, durasiFrame));

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
private:
rawMotorik rm;
  public:
    
      void bc(int timex){
        if(currentState != IDLE) return;
        currentState = SPECIAL;
    for(int i = 0;i<timex;i++){
            rm.bicepCurl();
        }
        rm.bicepCurl();
        currentState = IDLE;
    }

    void fm(int timex){
        if(currentState != IDLE) return;
        currentState = SPECIAL;
        for(int i = 0;i<timex;i++){
            rm.flexMuscle();
        }
        currentState = IDLE;
    }

    void stance(){
      if(currentState != IDLE) return;
        currentState = SPECIAL;
        buzz();
        rm.stance();
        currentState = IDLE;
    }
};