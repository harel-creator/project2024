#include <iostream>

class BloomFilter{
    public:
    BloomFilter(){
    
    }
    
        std::size_t useHash(std::string url){
            std::hash<std::string> myStringHash;
            return myStringHash("http")%8;
        }
    
};