#pragma once
#ifndef BLOOMFILTERAPP
#define BLOOMFILTERAPP

#include "BloomFilter.h"
#include <vector>
#include <string>
#include "HelpFunctions.h"
#include <istream>

// The class that sets the filter up, and starts running it. 
class BloomFilterApp {
    private:
        BloomFilter* bloomFilter;       //Pointer to the Bloomfilter the app uses which is saved in the heap.
    public:

        // Default constructor of the app, should be used from main.
        BloomFilterApp();

        // Destructor.
        ~BloomFilterApp();

        /**
         * Ensures that the input string for  building the bloomfilter is proper.
         * @param userInput The settings of the bloom filter:
           (First word- the size of the filter, The rest of the words- the hash functions to be used)
         * @return true IFF the received string is a proper input to build a bloom filter with.
         */
        static bool isSetupInputProper(std::string userInput);

        /**
         * Builds the bloomfilter after getting proper user input.
           (until it gets a suitable input, preforms endless loop)
         */
        void setUp();

        /**
         * Starts the infinite loop that deals with commands and requests of the user.
         */
        void run();
        
};

#endif