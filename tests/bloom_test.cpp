#include <gtest/gtest.h>
#include "../src/BloomFilter.cpp" // here we include the code to be tested
//#include "../src/OneHashFunc.cpp"
//#include "../src/HashFunc.cpp"
TEST(FilterTest, BasicTest) {
    BloomFilter bl;

    EXPECT_EQ(bl.useHash("www.example.com0"), 3);
    //empty string

    EXPECT_EQ(bl.useHash(""), 6);
    
}
TEST(HashFunc, HashBasicTest){
    OneHashFunc hf;
    std::hash<std::string> myStringHash;
    EXPECT_EQ(hf.hash("6"), myStringHash("6")%8);
}

