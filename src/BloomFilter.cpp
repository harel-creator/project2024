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
            this->filter.assign(8, false);            
        }
        BloomFilter(std::string str){
            std::vector<std::string> str_vector = split(str);
            if (str_vector.at(0) == "1")
            {
                std::cout<< str_vector.at(0)<<std::endl;
                this->hashF = new OneHashFunc();
            }else{
                //need to put here another type of HashFunc
            }
            this->filter = {};
            this->filter.assign(8, false);
            for(int i=0;i<str_vector.size();i++){
                std::cout<< str_vector.at(i)<<std::endl;
            }
            useHash(str_vector.back());
            
        }
        ~BloomFilter(){
            delete this->hashF;
        }
        /*
        get a string  url, and acrive an hash function on it.    
        */
        std::size_t useHash(std::string url){
 
            size_t index = this->hashF->hash(url);
            //In case the value in filter(index) is false we need to
            //shift it ti true
            if(!this->filter.at(index)){
                this->filter.at(index) = true;
            }
            return index;
        }

      
        /*
        split the str by "" to an array. Need to delete the array after use
        */
        std::vector<std::string> split(std::string str){
            std::vector<std::string> splited_str{};
            std::stringstream stream_str(str);
            std::string single_word = "";
            
            //every iteration put a full word to 'single_word', then push it to the 
            //end of the vector
            while(stream_str >> single_word){
                splited_str.push_back(single_word);
            }
            
            return splited_str;
        }
        
        bool getFilterIndex(int index)const{
            return this->filter.at(index);
        }

        
    
};