#include "HashFunc.h"

HashFunc::HashFunc(size_t size) {
    this->size = new size_t;
    *(this->size) = size;
}

HashFunc::~HashFunc() {
    delete this->size;
}