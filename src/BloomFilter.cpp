#include <iostream>
//#include "OneHashFunc.cpp"  // Consider avoiding including source files (.cpp) directly.
#include "BloomFilter.h"
#include "HelpFunctions.h"

// Constructor for BloomFilter
BloomFilter::BloomFilter() {
    this->hashF = new OneHashFunc();
    this->filter = {};
    this->filter.assign(8, false);
    this->blackList = {};
    this->filterSize = 8;
}

/**
 * @constructor for BloomFilter taking a string parameter
 * @param str A string parameter used for configuration
 */
BloomFilter::BloomFilter(std::string str) {
    std::vector<std::string> str_vector = split(str);
    this->filterSize = std::stoi(str_vector.at(0));

    this->hashF = new OneHashFunc(this->filterSize);
    this->blackList = {};
    
    // Create the filter with the appropriate size

    this->filter = {};
    this->filter.assign(this->filterSize, false);

    

    // Create the right hash function based on the size
    if (str_vector.at(1) == "1") {
        this->hashF = new OneHashFunc();
    } else {
        // Need to put here another type of HashFunc
    }
    
}



// Destructor for BloomFilter
BloomFilter::~BloomFilter() {
    delete this->hashF;
}

/**
 * @Check hash using the BloomFilter's hash function
 * @param str The input string to be hashed
 * @return The hash value
 */
size_t BloomFilter::checkHash(std::string str) {
    return this->hashF->hash(str);
}

/**
 * @Use hash function on a URL and update the filter and blacklist
 * @param url The URL to be processed
 * @return The hash index used
 */
std::size_t BloomFilter::useHash(std::string url) {
    size_t index = this->hashF->hash(url);

    // If the value in filter(index) is false, change it to true
    if (!this->filter.at(index)) {
        this->filter.at(index) = true;
        this->blackList.push_back(url);
    }

    return index;
}

/**
 * @Process a line of input and perform the corresponding operation
 * @param line The input line to be processed
 */
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
            // Need to add here the check if true positive or false positive
            // aka "true true" or "true false"
            std::cout << "true";
            urlInBlackList(str_vector.back());
        } else {
            std::cout << "false" << std::endl;
        }
    }
}

/**
 * @Check if a URL is in the blacklist
 * @param url The URL to be checked
 */
void BloomFilter::urlInBlackList(std::string url) const {
    for (const std::string str : this->blackList) {
        if (str == url) {
            std::cout << " true" << std::endl;
            return;
        }
    }
    // If we are here, it's because we looked and didn't find any match
    std::cout << " false" << std::endl;
}

/**
 * @Get the value at a specific index in the filter
 * @param index The index to be checked
 * @return The value at the specified index in the filter
 */
bool BloomFilter::getFilterIndex(int index) const {
    return this->filter.at(index);
}
int BloomFilter::getFilterSize(){
    return this->filterSize;
}
