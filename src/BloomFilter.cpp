#include <iostream>
//#include "OneHashFunc.cpp"
#include "BloomFilter.h"
#include "HelpFunctions.h"
//class BloomFilter{
    
    //public:
        BloomFilter::BloomFilter(){
            this->hashF = new OneHashFunc();
            this->filter = {};
            this->filter.assign(8, false);            
        }
        BloomFilter::BloomFilter(std::string str){
            this->hashF = new OneHashFunc();
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
        BloomFilter::~BloomFilter(){
            delete this->hashF;
        }

        size_t BloomFilter::checkHash(std::string str){
            return this->hashF->hash(str);
        }
        /*
        get a string  url, and acrive an hash function on it.    
        */
        std::size_t BloomFilter::useHash(std::string url){
            //std::cout<<url<<std::endl;
            size_t index = this->hashF->hash(url);
            //std::cout<<static_cast<int>(index)<<std::endl;
            //In case the value in filter(index) is false we need to
            //shift it ti true
            if(!this->filter.at(index)){
                this->filter.at(index) = true;
            }
            return index;
        }
        
        void BloomFilter::dealWithLine(std::string line){
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

      
        
        
        bool BloomFilter::getFilterIndex(int index)const{
            return this->filter.at(index);
        }

        
    
//};