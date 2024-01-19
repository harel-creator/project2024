#pragma once
#ifndef ONEHASHFUNC
#define ONEHASHFUNC

#include "HashFunc.h"

// The class for the url hashing function that hashes once: the 1-hash function. 
class OneHashFunc: public HashFunc
{
    public:
        // Default constructor: creates a 1-hash function with output range 8.
        OneHashFunc();

        /**
         * A constructor that creates a 1-hash function with a specific output range.
         * @param size The range of the hash function 0, ... , size-1.
        */
        OneHashFunc(size_t size);

        /**
         * Hashes a URL using the std::hash function, into the correct range.
         * @param url The input URL to be hashed
         * @return The hash value in the range.
         */
        size_t hash(std::string url) override;
};

#endif