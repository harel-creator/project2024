#pragma once
#ifndef BLOOMFILTER
#define BLOOMFILTER

#include <vector>
#include <string>

#include "NumHashFunc.h"

// A class that contains the logic of the Bloom Filter.
class BloomFilter {
private:
    const int DEFAULT_FILTER_SIZE = 8;
    std::vector<HashFunc*> hashF;  // Pointer to list of hash function objects
    std::vector<bool> filter;            // Bit array representing the filter
    std::vector<std::string> blackList;  // List of blacklisted URLs
    int filterSize;                   // The size of the filter

public:
    // Default Constructor for BloomFilter
    BloomFilter();

    /**
     * @constructor for BloomFilter taking a string parameter
     * @param str A string parameter used for configuration:
       (first word- the filter size, the following words- which hashing functions to use)
     */
    BloomFilter(std::string str);

    // Destructor
    ~BloomFilter();

    /**
     * Uses the hash functions on str, and return the value of hash(str)
     * @param str The URL to be processed
     * @return The hash value
     */
    std::vector<size_t> checkHash(std::string str);

    /**
     * @Use hash function on a URL and update the filter and blacklist
     * @param url The URL to be processed
     * @return The hash index used
     */
    std::size_t useHash(std::string url);

    /**
     * Processes a line of input and performs the corresponding operation
     * @param line The input line to be processed
     * @note probably better to put it in a different class later.
     */
    void dealWithLine(std::string line);

    /**
     * @Check if a URL is in the blacklist
     * @param url The URL to be checked
     */
    void urlInBlackList(std::string url) const;

    /**
     * @Get the value at a specific index in the filter
     * @param index The index to be checked
     * @return The value at the specified index in the filter
     */
    bool getFilterIndex(size_t index) const;

    /**
     * @return the size of the filter (how many bits we keep)
    */
    int getFilterSize();
};

#endif
