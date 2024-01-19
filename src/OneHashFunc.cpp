#include "OneHashFunc.h"

 OneHashFunc::OneHashFunc() : HashFunc(8) {}

 OneHashFunc::OneHashFunc(size_t size) : HashFunc(size){}

size_t OneHashFunc::hash(std::string url) {
    std::hash<std::string> myStringHash;

    return myStringHash(url) % *(this->size);
}
