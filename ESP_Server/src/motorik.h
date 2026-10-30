#pragma once
enum state{
IDLE, 
MAJU,
MUNDUR,
KANAN,
KIRI,
JOGET
};
state currentState = IDLE;
class rawMotorik{
    public:
void kakiKananMaju(){

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

    motorik(){
        bool buffer;
        EEPROM.get(0, buffer);
        if(!buffer){
            Serial.println("Something is wrong...");
            return;
        }
        EEPROM.write(0, false);
    }
void maju(int timex){
    if(!isIdle) return;
    currentState = MAJU;
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
for(int i =0;i<timex;i++){
    if(i==0 || i%2 == 0){
        rm.kakiKiriMundur();
    }else{
        rm.kakiKananMundur();
    }
}
}
void belokKanan(int timex){

}

void belokKiri(int timex){


}

~motorik(){
    EEPROM.write(0, true);
}
};

class joget{
  //to be continued...
};