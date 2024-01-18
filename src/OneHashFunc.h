#pragma once
#ifndef ONEHASHFUNC
#define ONEHASHFUNC

#include "HashFunc.h"
class OneHashFunc: public HashFunc
{
    private:
        /* data */
    public:
    
        //OneHashFunc(): HashFunc(){};

        std::size_t hash(std::string url) override;
};
#endif