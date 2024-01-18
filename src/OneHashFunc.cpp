#include "OneHashFunc.h"

// Constructor: Uncomment if needed
// OneHashFunc::OneHashFunc() : HashFunc() {}

// Destructor: Uncomment if needed
// OneHashFunc::~OneHashFunc() {}

/**
 * @Hash a URL using the std::hash function and modulo 8
 * @param url The input URL to be hashed
 * @return The hash value modulo 8
 */
std::size_t OneHashFunc::hash(std::string url) {
    std::hash<std::string> myStringHash;
    return myStringHash(url) % 8;
}
