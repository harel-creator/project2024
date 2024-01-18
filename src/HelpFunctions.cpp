#include "HelpFunctions.h"

/*
split the str by "" to an array. Need to delete the array after use
*/
std::vector<std::string> split(std::string str){
    std::vector<std::string> splited_str{};
    std::stringstream stream_str(str);
    std::string single_word = "";
    
    //every iteration put a full word to 'single_word', then push it to the 
    //end of the vector
    while(stream_str >> single_word){
        splited_str.push_back(single_word);
    }
    
    return splited_str;
}