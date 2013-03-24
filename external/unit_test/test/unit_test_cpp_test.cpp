/** @file unit_test_cpp_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

TEST(AutoRegisterTest)
{
}

IGNORE_TEST(IgnoreCPPTest)
{
    FAIL("C++ failure");
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
    int* a = (int*)0xDEADBEEF;
    int* b = (int*)0xDEADBEEF;
    int* c = (int*)0xBEEFDEAD;
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

struct TestFixture
{
    TestFixture()
        : test_int(42)
    {
    }
    ~TestFixture() {}

    int test_int;
};

TEST_FIXTURE(TestFixture, MakeAFixture)
{
    CHECK_EQUAL(42, test_int);
}
