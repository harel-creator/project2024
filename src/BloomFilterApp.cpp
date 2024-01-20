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
            std::vector<std::string> str_vector = split(user_input);
            if (std::stoi(str_vector.at(0)) == 0)
                return false;
            for (int i = 1; i < str_vector.size(); ++i) {
                if (std::stoi(str_vector.at(i)) <= 0)
                    return false;
            }
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
