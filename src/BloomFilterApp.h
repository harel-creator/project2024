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