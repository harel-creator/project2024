#pragma once
#ifndef HASHFUNC
#define HASHFUNC

#include <iostream>

// A class the represents a hash function that hashes urls.
class HashFunc
{
    protected:
        // The range of values of the hash function: 0, ... , range-1.
        int *range;

    public:
        /**
         * Constructor that creates a hash function with a specific output range.
         * @param range the range of the outpu range 0, ... , range-1.
         */
        HashFunc(int range);

        // Destructor.
        ~HashFunc();

        /**
         * The abstract function that does the hashing.
         * @param url The url to hash.
         * @return the hashed value of the given url.
         */
        virtual std::size_t hash(std::string url) = 0;

};

#endif