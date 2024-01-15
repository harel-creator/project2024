#include <gtest/gtest.h>
#include "../src/BloomFilter.cpp" // here we include the code to be tested
TEST(SumTest, BasicTest) {
    BloomFilter bl;
    EXPECT_EQ(bl.useHash("http"), 5);
}
