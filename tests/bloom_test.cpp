#include <gtest/gtest.h>
#include "../src/BloomFilter.h"
#include "../src/HashFunc.h"
#include "../src/HelpFunctions.h"
#include "../src/NumHashFunc.h"
#include "../src/HashFunc.cpp"
#include "../src/HelpFunctions.cpp"
#include "../src/NumHashFunc.cpp"
#include "../src/BloomFilter.cpp"
#include "../src/BloomFilterApp.h"
#include "../src/BloomFilterApp.cpp"
// Testing useHash:
TEST(FilterTest, BasicTest) {
    BloomFilter bl;

    EXPECT_EQ(bl.useHash("www.example.com0"), 3);

    // Test hashing an empty string:
    EXPECT_EQ(bl.useHash(""), 6);
    
}

// Testing the basic hash function:
TEST(HashFunc, HashBasicTest){
    NumHashFunc hf;
    std::hash<std::string> myStringHash;
    EXPECT_EQ(hf.hash("6"), myStringHash("6")%8);
}

// Testing the constructors of BloomFilter class:
TEST(FilterTeset,ConstarctorTest){
    BloomFilter bl;

    // Test the default constructor:
    for (int i =0; i < bl.getFilterSize(); i++){
        EXPECT_EQ(bl.getFilterIndex(i), false);
    }

    // Test the constructor that requires an array size:
    BloomFilter bl1("128 1");
    for (int i =0; i < bl1.getFilterSize(); i++){
        EXPECT_EQ(bl1.getFilterIndex(i), false);
    }
}

// Testing the split function:
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

    s = "2 1 www.com11";  
    ans = {"2", "1", "www.com11"}; 
    splited_str = split(s);

    ASSERT_EQ(splited_str.size(),ans.size());
    for (int i = 0; i < ans.size(); i++){
        EXPECT_EQ(splited_str[i], ans[i]);
    }
}

// Testing the filtering of BloomFilter:
TEST(FilterTests, BasicFilterTest){
    BloomFilter b1;
    b1.useHash("www.example.com0");

    EXPECT_EQ(b1.getFilterIndex(3), true);
    
    //empty string
    b1.useHash("");
    EXPECT_EQ(b1.getFilterIndex(6), true);
    for(int i = 0;i<8; i++){
        if( i != 3 && i != 6){
            EXPECT_EQ(b1.getFilterIndex(i), false);
        }else{
            EXPECT_EQ(b1.getFilterIndex(i), true);
        }
    }

}


// Testing dealWithLine method of BloomFilter:
TEST(FilterTest, AddURLTest){
    BloomFilter b1;
    b1.dealWithLine("1 www.example.com0");

    for(int i = 0;i<8; i++){
        if( i != 3 ){
            EXPECT_EQ(b1.getFilterIndex(i), false);
        }else{
            EXPECT_EQ(b1.getFilterIndex(i), true);
        }
    }
}

// Testing BloomFilter output:
TEST(FilterTest, checkOnly){
    testing::internal::CaptureStdout();
    BloomFilter b1;
    b1.dealWithLine("2 com");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "false\n");

    b1.dealWithLine("2 www.example.com0");
    EXPECT_EQ(output, "false\n");
}

// Testing BloomFilter output 2:
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

// Testing false positives:
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

//
TEST(AlmostFinalTEST, finalOne){

    BloomFilter b1;
    NumHashFunc n;

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
//
TEST(SetUpTests, notNumberSize){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("a 1"), false);
}
//
TEST(SetUpTests, notNumberHash){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("8 a"), false);
}
//
TEST(SetUpTests, zeroSize){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("0 1"), false);
}
//
TEST(SetUpTests, zeroHash){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("8 0"), false);
}
TEST(SetUpTests, negSize){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("-1 1"), false);
}
TEST(SetUpTests, negHash){
    EXPECT_EQ(BloomFilterApp::setUpInPutCheck("8 -1"), false);
}

//
TEST(FilterTests, addtionToListIfSameHash){

    BloomFilter b1;

    testing::internal::CaptureStdout();
    b1.dealWithLine("1 www.example.com0");
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, "");

    testing::internal::CaptureStdout();
    b1.dealWithLine("1 www.example.com1");
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, "");

    testing::internal::CaptureStdout();
    b1.dealWithLine("2 www.example.com1");
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, "true true\n");
}
