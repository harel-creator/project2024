#include <iostream>
//#include "OneHashFunc.cpp"  // Consider avoiding including source files (.cpp) directly.
#include "BloomFilter.h"
#include "HelpFunctions.h"

BloomFilter::BloomFilter() {
    this->hashF = new OneHashFunc();
    this->filter = {};
    this->filter.assign(DEFAULT_FILTER_SIZE, false);
    this->blackList = {};
    this->filterSize = DEFAULT_FILTER_SIZE;
}

BloomFilter::BloomFilter(std::string str) {
    // We first split the input string into words:
    std::vector<std::string> str_vector = split(str);

    // From it we can easily find the size of the filter and create the rest of it:
    this->filterSize = std::stoi(str_vector.at(0));
    this->hashF = new OneHashFunc(this->filterSize, std::stoi(str_vector.at(1)));
    this->blackList = {};    
    this->filter = {};
    this->filter.assign(this->filterSize, false);
}

BloomFilter::~BloomFilter() {
    delete this->hashF;
}

size_t BloomFilter::checkHash(std::string str) {
    return this->hashF->hash(str);
}

std::size_t BloomFilter::useHash(std::string url) {
    size_t index = this->hashF->hash(url);

    // If the value in filter(index) is false, change it to true
    if (!this->filter.at(index)) {
        this->filter.at(index) = true;
        this->blackList.push_back(url);
    } else {
        for (const std::string str : this->blackList) {
            if (str == url) {
                return index;
            }
        }
        // If we are here, it's because we looked and didn't find any match:
        this->blackList.push_back(url);
    }
    return index;
}

void BloomFilter::dealWithLine(std::string line) {
    std::vector<std::string> str_vector = split(line);

    // Add a URL
    if (str_vector.at(0) == "1") {
        // Assume that the last element is always the URL we need to check
        useHash(str_vector.back());
    } else if (str_vector.at(0) == "2") {
        // Check if the URL is in the blacklist or not
        bool flag = this->filter.at(checkHash(str_vector.back()));
        if (true == flag) {
            std::cout << "true";
            urlInBlackList(str_vector.back());
        } else {
            std::cout << "false" << std::endl;
        }
    }
}

void BloomFilter::urlInBlackList(std::string url) const {
    for (const std::string str : this->blackList) {
        if (str == url) {
            std::cout << " true" << std::endl;
            return;
        }
    }
    // If we are here, it's because we looked and didn't find any match:
    std::cout << " false" << std::endl;
}

bool BloomFilter::getFilterIndex(int index) const {
    return this->filter.at(index);
}
size_t BloomFilter::getFilterSize(){
    return this->filterSize;
}
