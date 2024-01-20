#include <iostream>

#include "BloomFilter.h"
#include "HelpFunctions.h"
#include "VectorBlacklist.h"

const std::string BloomFilter::BLACKLIST_URL = "1";
const std::string BloomFilter::IS_URL_BLACKLISTED = "2";

BloomFilter::BloomFilter() {
    this->filterSize = DEFAULT_FILTER_SIZE;

    this->filter = {};
    this->filter.assign(DEFAULT_FILTER_SIZE, false);

    this->hashFunctions = {};
    this->hashFunctions.push_back(new NumHashFunc());

    this->blackList = new VectorBlacklist;
}

BloomFilter::BloomFilter(std::string str) {
    // We first split the input string into words:
    std::vector<std::string> strVector = split(str);

    // From it we can easily find the size of the filter and create the rest of it:
    this->filterSize = std::stoi(strVector.at(0));

    this->filter = {};
    this->filter.assign(this->filterSize, false);

    this->hashFunctions = {};
    for (int i = 1; i < strVector.size(); ++i) {
        this->hashFunctions.push_back(new NumHashFunc(this->filterSize, std::stoi(strVector.at(i))));
    }

    // We can always change it to another type of blacklist if we need:
    this->blackList = new VectorBlacklist;
}

BloomFilter::~BloomFilter() {
    for (HashFunc* hashFunction : this->hashFunctions) {
        if (hashFunction != nullptr)
            delete hashFunction;
    }

    if (this->blackList != nullptr)
        delete this->blackList;
}

std::vector<size_t> BloomFilter::applyHash(std::string str) {
    std::vector<size_t> hashIds = {};
    for (HashFunc* hashFunction : this->hashFunctions) {
        hashIds.push_back(hashFunction->hash(str));
    }

    return hashIds;
}

void BloomFilter::addToBlacklist(std::string url) {
    // Turn on all the bits of the hashed url, to 1:
    std::vector<size_t> bitIndexes = applyHash(url);
    for (size_t index : bitIndexes) 
        this->filter.at(index) = 1;

    this->blackList->blacklistURL(url);
}

bool BloomFilter::isURLSuspicous(std::string url) {
    std::vector<size_t> bitIndexes = applyHash(url);

    for (size_t index : bitIndexes) {
        // If we found any bit that is 0, the url is definitely not blacklisted:
        if (!this->filter.at(index))
            return false;
    }

    // If all bits are on, the url is possibly blacklisted:
    return true;
}

void BloomFilter::dealWithLine(std::string line) {
    std::vector<std::string> tokens = split(line);
    // All proper lines contain exactly 2 tokens, the operation and a url:
    if (tokens.size() != 2) 
        return;

    std::string operation = tokens.at(0);
    std::string url = tokens.at(1);
    if (operation == BloomFilter::BLACKLIST_URL) {
        // Add  url to the blacklist:
        addToBlacklist(url);

    } else if (operation == BloomFilter::IS_URL_BLACKLISTED) {
        bool isSuspicous = isURLSuspicous(url);

        if (!isSuspicous) {
            // The url is't suspicous, we stop here:
            std::cout << "false" << std::endl;
            return;
        }

        std::cout << "true ";
        std::cout << std::boolalpha << this->blackList->isURLBlacklisted(url) << std::noboolalpha << std::endl;
    }
}

bool BloomFilter::getFilterIndex(size_t index) const {
    return this->filter.at(index);
}
int BloomFilter::getFilterSize(){
    return this->filterSize;
}
