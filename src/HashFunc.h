#pragma once
#ifndef HASHFUNC
#define HASHEFUNC

#include <iostream>

class HashFunc
{
    protected:
        int size;
        HashFunc();
    public:
        /*HashFunc();*/
        ~HashFunc(){}

        virtual std::size_t hash(std::string url)=0;

};
#endif