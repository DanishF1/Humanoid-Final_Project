#include<iostream>
#include <cctype>
#include "class.h"
#include "json.hpp"
using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return ""; // Jika string hanya berisi karakter kosong
    
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void processingInput(string input){
for(int i=0;i<input.length();i++){
    input[i]=tolower(input[i]);
}
input = trim(input);

}



int main(){
while(true){
string input;
cin>>input;
if(input=="exit" ||input == "q"){exit(0);}
}   
}