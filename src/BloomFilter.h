#pragma once
#ifndef BLOOMFILTER
#define BLOOMFILTER

#include <vector>
#include <string>
//#include <sstream>
//#include "HashFunc.h"  // Consider adding this include if needed.
#include "OneHashFunc.h"

class BloomFilter {
private:
    HashFunc* hashF;            // Pointer to the hash function object
    std::vector<bool> filter;    // Bool array representing the filter
    std::vector<std::string> blackList;  // List of blacklisted URLs

public:
    // Default constructor
    BloomFilter();

    // Overloaded constructor with a string parameter for configuration
    BloomFilter(std::string str);

    // Destructor
    ~BloomFilter();

    // Function to check hash using the BloomFilter's hash function
    size_t checkHash(std::string str);

    /**
     * @Use hash function on a URL and update the filter and blacklist
     * @param url The URL to be processed
     * @return The hash index used
     */
    std::size_t useHash(std::string url);

    // Process a line of input and perform the corresponding operation
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
    bool getFilterIndex(int index) const;
};

#endif
