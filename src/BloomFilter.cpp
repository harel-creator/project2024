#include <iostream>
#include "OneHashFunc.cpp"
class BloomFilter{
    private:
        HashFunc* hashF;
    public:
        BloomFilter(){
            this->hashF = new OneHashFunc();
        }
        ~BloomFilter(){
            delete this->hashF;
        }
        /*
        get a string  url, and acrive an hash function on it.    
        */
        std::size_t useHash(std::string url){
            std::hash<std::string> myStringHash;
            return this->hashF->hash(url);
        }

        
    
};