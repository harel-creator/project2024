#include <iostream>
//#include <sstream>
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
        /*
        split the str by "" to an array. Need to delete the array after use
        */
        std::string* split(std::string str){
            std::stringstream stream_str(str);
            std::string single_word = "";
            std::string* string_array = new std::string[2];
            int i = 0;
            while(stream_str >> single_word){
                string_array[i] = single_word;
                i++;
            }
            return string_array;
        }
        

        
    
};