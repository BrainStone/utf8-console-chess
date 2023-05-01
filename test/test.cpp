// Dummy test file
#include "gtest/gtest.h"

TEST(Dummy, Success) {
    EXPECT_LT(1, 2);
}

TEST(Dummy, Failure) {
    EXPECT_LT(2, 1);
}
