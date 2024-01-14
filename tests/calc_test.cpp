#include <gtest/gtest.h>
#include "../src/calc.cpp" // here we include the code to be tested
TEST(SumTest, BasicTest) {
    EXPECT_EQ(sum(1,2), 3);
}