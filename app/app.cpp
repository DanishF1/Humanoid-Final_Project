#include<iostream>
#include <cctype>
#include "class.h"
using namespace std;
parsingAndSend p;
bool valid = false;
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // Jika string hanya berisi karakter kosong
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void processingInput(string input){
string validcmd[4] = {"w", "s", "a", "d"};
for(int i=0;i<input.length();i++){
    input[i]=tolower(input[i]);
}
input = trim(input);
for (int j=0;j<(sizeof(validcmd)/sizeof(validcmd[0]));j++){
    if(input == validcmd[j]){
        valid = true;
        cout<<"Processing..."<<endl;
        p.parsing(j);
        break;
    }else if(j==3 && input != validcmd[j]){
        valid = false;
        cout<<"Command not found"<<endl;
    }
}

}

int main(){
while(true){
valid = false;
string input;
cin>>input;

if(input=="exit" ||input == "q"){
    exit(0);
}else{
    processingInput(input);
}
}   
}