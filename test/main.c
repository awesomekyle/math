/** @file main.c
 *  @copyright Copyright (c) 2014 Kyle Weicht. All rights reserved.
 */
#include "gtest/gtest.h"

/* External functions
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

