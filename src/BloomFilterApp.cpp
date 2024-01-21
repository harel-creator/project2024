#include <vector>
#include <string>
#include <istream>
#include <utility> //for pair

#include "BloomFilterApp.h"
#include "BloomFilter.h"
#include "SetupParser.h"


BloomFilterApp::BloomFilterApp() {
    this->bloomFilter = nullptr;
}

void BloomFilterApp::setUp() {
    std::string userInput = "";
    SetupParser sp;

    bool setupDone = false;
    std::pair<int, std::vector<HashFunc*>> setupInfo;
    while (!setupDone) {
        try {
            std::getline(std::cin, userInput);
            setupInfo = sp.ParseSetup(userInput);

            // If we got here, that means ParseSetup didn't throw an error
            // So it received proper input:
            setupDone = true;
        } catch (...) {}
    }

    this->bloomFilter = new BloomFilter(setupInfo.first, setupInfo.second);
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
