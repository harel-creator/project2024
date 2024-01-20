#include <iostream>
//#include "OneHashFunc.cpp"  // Consider avoiding including source files (.cpp) directly.
#include "BloomFilter.h"
#include "HelpFunctions.h"

BloomFilter::BloomFilter() {
    this->hashF = {};
    this->hashF.push_back(new NumHashFunc());
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
    this->hashF = {};
    for (int i = 1; i < str_vector.size(); ++i) {
        this->hashF.push_back(new NumHashFunc(this->filterSize, std::stoi(str_vector.at(i))));
    }
    this->blackList = {};    
    this->filter = {};
    this->filter.assign(this->filterSize, false);
}

BloomFilter::~BloomFilter() {
    for (HashFunc* hashItem : this->hashF) {
        if (hashItem != nullptr)
            delete hashItem;
    }
    }

std::vector<size_t> BloomFilter::checkHash(std::string str) {
    std::vector<size_t> hashIds = {};
    for (HashFunc* hashItem : this->hashF) {
        hashIds.push_back(hashItem->hash(str));
    }
    return hashIds;
}

std::size_t BloomFilter::useHash(std::string url) {
    std::size_t index = this->hashF.at(0)->hash(url);
    // If the value in filter(index) is false, change it to true
    for (const std::string str : this->blackList) {
        if (str == url) {
            return index ;
        }
    }
    // If we are here, it's because we looked and didn't find any match:
    this->blackList.push_back(url);
    for (HashFunc* hashItem : this->hashF) {
        size_t index = hashItem->hash(url);
        if (!this->filter.at(index)) {
            this->filter.at(index) = true;
        }
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
        std::vector<size_t> indexes = checkHash(str_vector.back());
        bool flag = true;
        for (size_t id : indexes) {
            flag = flag & this->filter.at(id);
        }
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

bool BloomFilter::getFilterIndex(size_t index) const {
    return this->filter.at(index);
}
int BloomFilter::getFilterSize(){
    return this->filterSize;
}
