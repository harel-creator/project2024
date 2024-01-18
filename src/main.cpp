#include "BloomFilter.h"
#include<vector>
#include<string>
//#include "HashFunc.h"
#include "HelpFunctions.h"
#include <istream>

int main(int argc, char** argv) {
    std::string user_input;
    bool flag_user_input = true;
    
    while(flag_user_input){
        std::getline(std::cin, user_input);
        std::vector<std::string> str_vector = split(user_input);
        if(str_vector.size()!=3){
            //the input is ok?
        }else{
            flag_user_input =false;
        }
    }
    BloomFilter bl(user_input);
    //main loop
    while(true){
        std::getline(std::cin, user_input);
        if(user_input == ""){
            continue;
        }
        bl.dealWithLine(user_input);
    }
    return 0;
}