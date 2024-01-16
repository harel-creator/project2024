#include "HashFunc.cpp"

class OneHashFunc: public HashFunc
{
private:
    /* data */
public:
    
    OneHashFunc(): HashFunc(){}
    /*~OneHashFunc: public HashFunc();*/

    std::size_t hash(std::string url) override{
        std::hash<std::string> myStringHash;
        return myStringHash(url)%8;
    }
};
