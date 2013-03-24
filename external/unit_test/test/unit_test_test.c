/** @file unit_test_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

#include <stdio.h>

TEST(MakeTest)
{
}
IGNORE_TEST(FailTest)
{
    FAIL("Failure!");
}
TEST(BoolChecks)
{
    CHECK_TRUE(1);
    CHECK_FALSE(0);
}
TEST(CheckIntEqual)
{
    CHECK_EQUAL(33, 33);
    CHECK_NOT_EQUAL(-56, 56);
}
TEST(CheckIntLTGT)
{
    CHECK_LESS_THAN(458, 558);
    CHECK_GREATER_THAN(-564, -664);
    CHECK_LESS_THAN_EQUAL(458, 558);
    CHECK_LESS_THAN_EQUAL(458, 458);
    CHECK_GREATER_THAN_EQUAL(-564, -564);
    CHECK_GREATER_THAN_EQUAL(-564, -664);
}
TEST(CheckPointerEqual)
{
    int i[3];
    int* a = i+0;
    int* b = i+0;
    int* c = i+2;
    int* d = NULL;
    CHECK_EQUAL_POINTER(a, b);
    CHECK_NOT_EQUAL_POINTER(a, c);
    CHECK_NULL(d);
    CHECK_NOT_NULL(a);
}
TEST(CheckFloatEqual)
{
    CHECK_EQUAL_FLOAT(33.9234f, 33.9233f);
    CHECK_NOT_EQUAL(-56.233f, 56.985f);
}
TEST(CheckFloatLTGT)
{
    CHECK_LESS_THAN_FLOAT(458.134f, 558.3284f);
    CHECK_GREATER_THAN(-564.324f, -664.23423f);
    CHECK_LESS_THAN_EQUAL(458.53f, 558.75f);
    CHECK_LESS_THAN_EQUAL(458.123f, 458.1234f);
    CHECK_GREATER_THAN_EQUAL(-564.345f, -564.345f);
    CHECK_GREATER_THAN_EQUAL(-564.324f, -664.873f);
}
TEST(CheckString)
{
    const char* a = "Hello World";
    const char* b = "Hello World";
    const char* c = "Goodbye world";
    CHECK_EQUAL_STRING(a, b);
    CHECK_NOT_EQUAL_STRING(a, c);
}


TEST_MODULE(unit_test)
{
    REGISTER_TEST(MakeTest);
    REGISTER_TEST(FailTest);
    REGISTER_TEST(BoolChecks);
    REGISTER_TEST(CheckIntEqual);
    REGISTER_TEST(CheckIntLTGT);
    REGISTER_TEST(CheckPointerEqual);
    REGISTER_TEST(CheckFloatEqual);
    REGISTER_TEST(CheckFloatLTGT);
    REGISTER_TEST(CheckString);
}
