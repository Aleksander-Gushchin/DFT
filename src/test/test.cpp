#include <gtest/gtest.h>
#include "lib.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  // Expect equality.
  EXPECT_EQ(get_string(), std::string("ggg"));
}