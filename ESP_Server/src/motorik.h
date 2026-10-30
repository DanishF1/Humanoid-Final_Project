#pragma once

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
    motorik(){
    }
void maju(int timex){
for(int i =0;i<timex;i++){
    if(i==0 || i%2 == 0){
        rm.kakiKananMaju();
    }else{
        rm.kakiKiriMaju();
    }
}
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
};

class joget{
  //to be continued...
};