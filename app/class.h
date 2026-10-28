#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <limits>
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
    vector<string> moves = doc["moves"].get<vector<string>>();
    string payloadRaw;
    for(int i = 0;i<moves.size();i++){
        if(i==0 || i==moves.size()){
            payloadRaw += moves[i];
        }else{
            payloadRaw += ','+moves[i];
        }
    }
    string payload = '{' + payloadRaw +'}';
    cout<<payload<<endl;
    sendKebridge(payload);
}

void sendKebridge(string data){
string port = "/dev/ttyUSB0";

    string configCmd = "stty -F " + port + " 115200 raw -echo min 0 time 50";
    system(configCmd.c_str());

    fstream serial(port, ios::in | ios::out);
    if (!serial.is_open()) {
        cout << "ESP32 Not found" << endl;
        return;
    }

    serial << data<<"\n";
    serial.flush();

    string respon;
    bool dapat = false;
    while (getline(serial, respon)) {              
            cout << "Wahai customer: " << respon << endl;
    }
    if (!dapat) {
        cout << "No Respond" << endl;
    }
}

};