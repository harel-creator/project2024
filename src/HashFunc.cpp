#include <iostream>

class HashFunc 
{
    private:
        /* data */
    public:
        /*HashFunc();
        ~HashFunc();*/

        virtual std::size_t hash(std::string url)=0;

};
