#include "polyn2.h"

#include <gtest/gtest.h>

TEST(MathTest, TwoPlusTwoEqualsFour) {
    EXPECT_EQ(2 + 2, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    std::cout << "END";
    return RUN_ALL_TESTS();
}