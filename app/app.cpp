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
using namespace std;
bool valid = false;
bool dapat = false;

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

    while (getline(serial, respon)) {              
            cout << "Respon ESP32: " << respon << endl;
            dapat = true;
            break;
    }
    if (!dapat) {
        cout << "No Respond" << endl;
    }
    
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; 
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void processingInput(string input, int timex){
string validcmd[6] = {"w", "s", "a", "d"};
for(int i=0;i<input.length();i++){
    input[i]=tolower(input[i]);
}
input = trim(input);
for (int j=0;j<(sizeof(validcmd)/sizeof(validcmd[0]));j++){
    if(input == validcmd[j]){
        valid = true;
        cout<<"Processing..."<<endl;
        break;
    }else if(j==3 && input != validcmd[j]){
        valid = false;
        cout<<"Command not found"<<endl;
    }
}
string Stimex;
if(timex<10){
Stimex = "0"+to_string(timex);
}else if(timex<99){
Stimex = to_string(timex);
}else{
Stimex = "00";
}
if (valid == true){
string payload = "FF" + input + Stimex;
cout<<payload<<endl;
sendKebridge(payload);
}else{
    return;
}


}

int main(){
cout<<"APP FINAL PROJECT VIROSE"<<endl;
cout<<"Danish - Programming"<<endl;
cout<<"Raisa - Mekanikal"<<endl;
cout<<"Fadil Setrum Setrum - Elektrikal"<<endl;

while(true){
cout<<endl;
valid = false;
dapat = false;
string input;
int timex;
cout<<"enter command + time it moves"<<endl;
cin>>input;
if(input=="exit" ||input == "q"){
    exit(0);
}else{
    cin>>timex;
processingInput(input, timex);
}

}   
}