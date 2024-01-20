#include "NumHashFunc.h"

 NumHashFunc::NumHashFunc() : HashFunc(8) {
     this->hashSize = 1;
}

 NumHashFunc::NumHashFunc(size_t size, size_t hashSize) : HashFunc(size){
     this->hashSize = hashSize;
}

size_t NumHashFunc::hash(std::string url) {
    std::hash<std::string> myStringHash;
    size_t outPut = myStringHash(url);
    for (int i = 1; i < this->hashSize; ++i) {
        outPut = myStringHash(std::to_string(outPut));
    }
    return outPut % *(this->size);
}
