#pragma once
#include<iostream>
#include <cctype>
#include <fstream>
#include "json.hpp"
nlohmann::json j;
using namespace std;

    enum cmd{
    maju,
    mundur,
    belok_kanan,
    belok_kiri
};


class parsingAndSend{
    public:
    using json = nlohmann::json;
void parsing(int number){   
    cout<<number<<endl;
    string Snumber = to_string(number);
    string path = "/home/dan-eksakdev/Documents/Final_Project2/app/moves_json/" + Snumber + ".json";
    fstream File;
    File.open(path);
    if(!File.is_open()){
            cout<<"Err, motion_movie file won't open!"<<endl;
        }
    json doc = json::parse(File);

    for (int i=0;i<doc["moves"][i].size();i++){
        cout<<doc["moves"][i]<<" ";
    }

    switch(number){
        case maju:
        break;

        case mundur:
        break;

        case belok_kanan:
        break;

        case belok_kiri:
        break;

    }
}

};