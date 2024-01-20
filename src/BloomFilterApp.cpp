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
                int functionID = std::stoi(str_vector.at(i));
                if (functionID <= 0 || functionID > HashFunc::NUM_OF_UNIQUE_FUNCTIONS)
                    return false;
            }

            return true;
        } catch(...) {
            return false;
        }
}

void BloomFilterApp::setUp() {
    std::string userInput = "";
    while (!BloomFilterApp::isSetupInputProper(userInput)) {
        std::getline(std::cin, userInput);
    }
    
    this->bloomFilter = new BloomFilter(userInput);
}

void BloomFilterApp::run() {
    std::string userInput;
    while (true) {
        std::getline(std::cin, userInput);
        if (userInput == "") {
            continue;  // Skip empty lines
        }

        this->bloomFilter->dealWithLine(userInput);
    }
}
