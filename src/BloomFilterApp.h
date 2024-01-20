#pragma once
#ifndef BLOOMFILTERAPP
#define BLOOMFILTERAPP

#include "BloomFilter.h"
#include <vector>
#include <string>
#include "HelpFunctions.h"
#include <istream>

// The class for the url hashing function that hashes once: the 1-hash function. 
class BloomFilterApp {
    private:
        BloomFilter* bloomFilter;       //pointer to Bloomfilter object
    public:

        // Default constructor of the app, shoud be used from main.
        BloomFilterApp();

        /**
         * ensures that the input is proper for building bloomfilter.
         * @param str The input of the user for set up
         * @return Is the in put sutble to init bloomfilter.
         */
        static bool setUpInPutCheck(std::string user_input);

        /**
         * bilds the bloomfilter after getting proper user input.
         * until get suteble input preform endless while loop.
         */
        void setUp();

        /**
         * start infinte loop that deal with commands and requests of the user.
         */
        void run();
        
};

#endif