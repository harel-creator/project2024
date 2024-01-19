#include "BloomFilter.h"
#include <vector>
#include <string>
#include "HelpFunctions.h"
#include <istream>
#include "BloomFilterApp.h"


BloomFilterApp::BloomFilterApp() {}

bool BloomFilterApp::setUpInPutCheck(std::string user_input) {
    std::vector<std::string> str_vector = split(user_input);
        if (str_vector.size() < 2) 
            return false;
        return true;
}
void BloomFilterApp::setUp() {
    std::string user_input = "";
    while (!BloomFilterApp::setUpInPutCheck(user_input)) {  //while input inappropriate continue request
        std::getline(std::cin, user_input);
    }
    this->bloomFilter = new BloomFilter(user_input);
}
void BloomFilterApp::run() {
    std::string user_input;
    while (true) {
        std::getline(std::cin, user_input);
        if (user_input == "") {
            continue;  // Skip empty lines
        }
        this->bloomFilter->dealWithLine(user_input);
    }
}
