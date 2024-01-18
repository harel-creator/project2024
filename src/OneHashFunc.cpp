
#include "OneHashFunc.h"

    //OneHashFunc::OneHashFunc(): HashFunc(){}
    /*~OneHashFunc: public HashFunc();*/

    std::size_t OneHashFunc::hash(std::string url) {
        std::hash<std::string> myStringHash;
        return myStringHash(url)%8;
    }