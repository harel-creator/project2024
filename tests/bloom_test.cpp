#include <gtest/gtest.h>
#include "../src/BloomFilter.h"
#include "../src/HashFunc.h"
#include "../src/HelpFunctions.h"
#include "../src/OneHashFunc.h"
#include "../src/HashFunc.cpp"
#include "../src/HelpFunctions.cpp"
#include "../src/OneHashFunc.cpp"
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

//test if the defualt constactor works
TEST(FilterTeset,EmptyConstarctorTest){
    BloomFilter bl;
    for (int i =0; i < bl.getFilterSize(); i++){
        EXPECT_EQ(bl.getFilterIndex(i), false);
    }
}

// Make sure that the split realy split by "".
TEST(SlpitTests, BasicSplitTest){
    BloomFilter bf;
    std::string s = "2 www.com11";
    std::vector<std::string> ans = {"2", "www.com11"}; 
    std::vector<std::string> splited_str;
    splited_str = split(s);
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
    splited_str = split(s);
    ASSERT_EQ(splited_str.size(),ans.size());
    for (int i = 0; i < ans.size(); i++){
        EXPECT_EQ(splited_str[i], ans[i]);
    }
}

TEST(FilterTests, BasicFilterTest){
    BloomFilter b1;
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

TEST(FilterTest, AddURLTest){
    BloomFilter b1;
    b1.dealWithLine("1 www.example.com0");
    //b1.useHash("");
    //and check everything
    for(int i = 0;i<8; i++){
        if( i != 3 ){
            EXPECT_EQ(b1.getFilterIndex(i), false);
        }else{
            EXPECT_EQ(b1.getFilterIndex(i), true);
        }
    }
}

TEST(FilterTest, checkOnly){
    testing::internal::CaptureStdout();
    BloomFilter b1;
    b1.dealWithLine("2 com");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "false\n");
    b1.dealWithLine("2 www.example.com0");
    EXPECT_EQ(output, "false\n");
    b1.dealWithLine("1 www.example.com0");

}

TEST(FilterTest, checkAndAddOnly){
    
    BloomFilter b1;
    b1.dealWithLine("1 www.example.com0");
    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com0");
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "true true\n");
    
    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com111");
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "false\n");
}

TEST(FilterTest, falsePositveCheck){
    BloomFilter b1;
    b1.dealWithLine("1 www.example.com0");
    testing::internal::CaptureStdout();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com0");
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "true true\n");

}
TEST(AlmostFinalTEST, finalOne){

    BloomFilter b1;
    OneHashFunc n;

    testing::internal::CaptureStdout();
    b1.dealWithLine("1 www.example.com0");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "");

    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com0");
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "true true\n");

    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com4");
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "false\n");

    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com11");
    std::string output4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output4, "true false\n");


}