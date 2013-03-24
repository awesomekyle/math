/** @file main.c
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include <stdio.h>
#include "unit_test.h"

/* Internal functions
 */
DECLARE_MODULE(unit_test);
static void register_tests(void)
{
    REGISTER_MODULE(unit_test);
}

/* External functions
 */
int main(int argc, const char* argv[])
{
    RUN_ALL_TESTS(argc, argv, "-t", register_tests);

    return 0;
}

