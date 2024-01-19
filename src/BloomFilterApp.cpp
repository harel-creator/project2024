#include "BloomFilter.h"
#include <vector>
#include <string>
#include <istream>
#include "BloomFilterApp.h"


BloomFilterApp::BloomFilterApp() {}

bool BloomFilterApp::setUpInPutCheck(std::string user_input) {
        try{
            BloomFilter* bl = new BloomFilter(user_input);
            delete bl;
            return true;
        } catch(...) {
            return false;
        }

}
void BloomFilterApp::setUp() {
    std::string user_input = "";
    while (!BloomFilterApp::setUpInPutCheck(user_input)) {
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
