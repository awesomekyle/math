/** @file main.c
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "unit_test.h"

/* Internal functions
 */
DECLARE_MODULE(math);
static void register_tests(void)
{
    REGISTER_MODULE(math);
}

/* External functions
 */
int main(int argc, const char* argv[])
{
    srand((unsigned int)time(NULL));
    RUN_ALL_TESTS(argc, argv, "-t", register_tests);

    return 0;
}

