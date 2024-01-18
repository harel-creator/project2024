#pragma once
#ifndef BLOOMFILTER 
#define BLOOMFILTER
#include <vector>
#include <string>
//#include <sstream>
//#include "HashFunc.h"
#include "OneHashFunc.h"
class BloomFilter{
    private:
        HashFunc* hashF;
        std::vector<bool> filter;
        std::vector<std::string> blackList;
    public:
        BloomFilter();
        BloomFilter(std::string str);
        ~BloomFilter();

        size_t checkHash(std::string str);
        /*
        get a string  url, and acrive an hash function on it.    
        */
        std::size_t useHash(std::string url);
        
        void dealWithLine(std::string line);

      
        /*
        split the str by "" to an array. Need to delete the array after use
        */
        //std::vector<std::string> split(std::string str);
        
        bool getFilterIndex(int index)const;
        void urlInBlackList(std::string url)const;
        
    
};
#endif