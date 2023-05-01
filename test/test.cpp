// Dummy test file
#include "gtest/gtest.h"

TEST(Dummy_1, Success) {
    EXPECT_LT(1, 2);
}

TEST(Dummy_1, Failure) {
    EXPECT_LT(2, 1);
}

TEST(Dummy_2, Success) {
    EXPECT_GT(2, 1);
}

TEST(Dummy_2, Failure) {
    EXPECT_GT(1, 2);
}
