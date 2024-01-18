#pragma once
#ifndef HASHFUNC
#define HASHFUNC

#include <iostream>

class HashFunc
{
public:
    // Virtual function for hashing a URL
    virtual std::size_t hash(std::string url) = 0;
};

#endif
