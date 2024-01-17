#include <iostream>
//#include <sstream>
#include "OneHashFunc.cpp"
class BloomFilter{
    private:
        HashFunc* hashF;
        std::vector<bool> filter;
    public:
        BloomFilter(){
            this->hashF = new OneHashFunc();
            this->filter = {};
    
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
        std::vector<std::string> split(std::string str){
            std::vector<std::string> splited_str{};
            std::stringstream stream_str(str);
            std::string single_word = "";

            while(stream_str >> single_word){
                splited_str.push_back(single_word);
            }
            
            /*std::cout<<"we start a new array, its size is: "<<splited_str.size()<<std::endl;
            for(auto word = splited_str.begin(); word!= splited_str.end(); word++){
                std::cout<<*word<<std::endl;
            }*/
            return splited_str;
        }
        

        
    
};