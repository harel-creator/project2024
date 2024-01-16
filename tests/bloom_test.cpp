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
// Make sure that the split realy split by "".
TEST(SlpitTest, BsicSplitTest){
    BloomFilter bf;
    std::string s = "2 www.com11";
    std::string ans[2] = {"2", "www.com11"}; 
    //bf.setInfo(bf.split(s));
    EXPECT_EQ(bf.split(s)->size(), ans->size());
    for (int i = 0; i <= ans->size(); i++){
        EXPECT_EQ(bf.split(s)[i], ans[i]);
    }

}

