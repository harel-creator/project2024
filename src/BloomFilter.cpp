#include <iostream>
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
            //create the fillter in the right size
            this->filter = {};
            this->filter.assign(std::stoi(str_vector.at(1)), false);
            
            //create the right hash function
            if (str_vector.at(1) == "1")
            {
                this->hashF = new OneHashFunc();
            }else{
                //need to put here another type of HashFunc
            }
            
            //useHash(str_vector.back());
            
        }
        ~BloomFilter(){
            delete this->hashF;
        }

        size_t checkHash(std::string str){
            return this->hashF->hash(str);
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
        
        void dealWithLine(std::string line){
            std::vector<std::string> str_vector = split(line);
            // add a url
            if (str_vector.at(0) == "1")
            {
                useHash(str_vector.back());
            }else if (str_vector.at(0) == "2"){
                bool flag = this->filter.at(checkHash(str_vector.back()));
                if (true == flag)
                {
                    //need to add here the check if true positive or false positive
                    // aka "true true" or "true false"
                    std::cout<<"true"<<std::endl;
                    
                }else{
                    std::cout<<"false"<<std::endl;
                }
            }
            
            
        }

      
        /*
        split the str by "" to an array. Need to delete the array after use
        */
        static std::vector<std::string> split(std::string str){
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