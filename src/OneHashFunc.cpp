#include "OneHashFunc.h"

 OneHashFunc::OneHashFunc() : HashFunc(8) {
     this->hashSize = 1;
}

 OneHashFunc::OneHashFunc(size_t size, size_t hashSize) : HashFunc(size){
     this->hashSize = hashSize;
}

size_t OneHashFunc::hash(std::string url) {
    std::hash<std::string> myStringHash;
    std::hash<size_t> myNumHash;
    size_t outPut = myStringHash(url);
    for (int i = 1; i < this->hashSize; ++i) {
        outPut = myNumHash(outPut);
    }
    return outPut % *(this->size);
}
