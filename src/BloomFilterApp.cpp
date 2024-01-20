#include <vector>
#include <string>
#include <istream>

#include "BloomFilterApp.h"
#include "BloomFilter.h"


BloomFilterApp::BloomFilterApp() {
    this->bloomFilter = nullptr;
}

BloomFilterApp::~BloomFilterApp() {
    if (this->bloomFilter != nullptr) {
        delete this->bloomFilter;
        this->bloomFilter = nullptr;
    }
}

bool BloomFilterApp::isSetupInputProper(std::string userInput) {
        try{
            std::vector<std::string> str_vector = split(userInput);

            // Check that the filter size is proper:
            int filterSize = std::stoi(str_vector.at(0));
            if (filterSize <= 0)
                return false;

            // Check that the hash functions are proper:
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
    while (!BloomFilterApp::isSetupInputProper(user_input)) {
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
