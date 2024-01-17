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
TEST(SlpitTests, BasicSplitTest){
    BloomFilter bf;
    std::string s = "2 www.com11";
    std::vector<std::string> ans = {"2", "www.com11"}; 
    std::vector<std::string> splited_str;
    splited_str = bf.split(s);
    ASSERT_EQ(splited_str.size(),ans.size());
    for (int i = 0; i < ans.size(); i++){
        EXPECT_EQ(splited_str[i], ans[i]);
    }
}
TEST(SlpitTests, BasicSplitTest2){
    BloomFilter bf;
    std::string s = "2 1 www.com11";  
    std::vector<std::string> ans = {"2", "1", "www.com11"}; 
    std::vector<std::string> splited_str;
    splited_str = bf.split(s);
    ASSERT_EQ(splited_str.size(),ans.size());
    for (int i = 0; i < ans.size(); i++){
        EXPECT_EQ(splited_str[i], ans[i]);
    }
}

TEST(FilterTests, BasicFilterTest){
    BloomFilter b1,b2;
    b1.useHash("www.example.com0");
    EXPECT_EQ(b1.getFilterIndex(3), true);
    
    //empty string
    b1.useHash("");
    EXPECT_EQ(b1.getFilterIndex(6), true);
    //and check every cell
    for(int i = 0;i<8; i++){
        if( i != 3 && i != 6 ){
            EXPECT_EQ(b1.getFilterIndex(i), false);
        }else{
            EXPECT_EQ(b1.getFilterIndex(i), true);
        }
    }

}