#include <gtest/gtest.h>
#include "../src/calc.cpp" // here we include the code to be tested
TEST(SumTest, BasicTest) {
    EXPECT_EQ(sum(1,2), 3);
}
TEST(SumTest, BasicTest1) {
    
    EXPECT_GE(sum(1,4), 5);
}
TEST(DecTest, BasicTest2) {
    EXPECT_GE(dec(1,4), -3);
}