/** @file unit_test.c
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#ifndef _WIN32
    #include <inttypes.h>
#endif

#ifndef PRId64
    #define PRId64 "ld"
#endif

#if defined(__APPLE__) || defined(__GNUG__)
    #define ERROR_FORMAT "%s:%d: error: "
#else
    #define ERROR_FORMAT "%s(%d): error: "
#endif

/* Constants
 */
enum {MAX_TESTS = 4096};
static const float EPSILON = 0.001f;

typedef enum {
    kResultPass,
    kResultFail,
    kResultIgnore
} test_result_t;

/* Variables
 */
static test_func_t* _test_funcs[MAX_TESTS] = {NULL};
static int  _num_tests = 0;
static int  _num_tests_passed = 0;
static int  _num_tests_failed = 0;
static int  _num_tests_ignored = 0;
static test_result_t _current_result = kResultPass;

/* Internal functions
 */

/* External functions
 */
void _fail(const char* file, int line, const char* format, ...)
{
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    printf("\n"ERROR_FORMAT"%s\n", file, line, buffer);
    _current_result = kResultFail;
}

/* bool checks */
void _check_true(const char* file, int line, int value)
{
    if(!value)
        _fail(file, line, "False");
}
void _check_false(const char* file, int line, int value)
{
    if(value)
        _fail(file, line, "True");
}

/* integer checks */
void _check_equal(const char* file, int line, int64_t expected, int64_t actual)
{
    if(expected != actual)
        _fail(file,line, "Expected: %"PRId64"  Actual: %"PRId64"", expected, actual);
}
void _check_not_equal(const char* file, int line, int64_t expected, int64_t actual)
{
    if(expected == actual)
        _fail(file,line, "Actual value equals expected: %"PRId64"", actual);
}
void _check_less_than(const char* file, int line, int64_t left, int64_t right)
{
    if(left >= right)
        _fail(file,line, "%"PRId64" is not less than %"PRId64"", left, right);
}
void _check_greater_than(const char* file, int line, int64_t left, int64_t right)
{
    if(left <= right)
        _fail(file,line, "%"PRId64" is not greater than %"PRId64"", left, right);
}
void _check_less_than_equal(const char* file, int line, int64_t left, int64_t right)
{
    if(left > right)
        _fail(file,line, "%"PRId64" is not less than %"PRId64"", left, right);
}
void _check_greater_than_equal(const char* file, int line, int64_t left, int64_t right)
{
    if(left < right)
        _fail(file,line,"%"PRId64" is not greater than %"PRId64"", left, right);
}

/* pointer checks */
void _check_equal_pointer(const char* file, int line, const void* expected, const void* actual)
{
    if(expected != actual)
        _fail(file,line, "Expected: %p  Actual: %p", expected, actual);
}
void _check_not_equal_pointer(const char* file, int line, const void* expected, const void* actual)
{
    if(expected == actual)
        _fail(file,line, "Actual value equals expected: %p", actual);
}
void _check_null(const char* file, int line, const void* pointer)
{
    if(pointer != NULL)
        _fail(file,line, "Pointer is not NULL: %p", pointer);
}
void _check_not_null(const char* file, int line, const void* pointer)
{
    if(pointer == NULL)
        _fail(file,line, "Pointer is NULL");
}

/* float checks */
void _check_equal_float(const char* file, int line, double expected, double actual)
{
    if(fabs(expected - actual) > EPSILON)
        _fail(file,line, "Expected: %f  Actual: %f", expected, actual);
}
void _check_not_equal_float(const char* file, int line, double expected, double actual)
{
    if(fabs(expected - actual) < EPSILON)
        _fail(file,line, "Actual value equals expected: %f", actual);
}
void _check_less_than_float(const char* file, int line, double left, double right)
{
    if(left >= right)
        _fail(file,line, "%f is not less than %f", left, right);
}
void _check_greater_than_float(const char* file, int line, double left, double right)
{
    if(left <= right)
        _fail(file,line, "%f is not greater than %f", left, right);
}
void _check_less_than_equal_float(const char* file, int line, double left, double right)
{
    if(left > right)
        _fail(file,line, "%f is not less than %f", left, right);
}
void _check_greater_than_equal_float(const char* file, int line, double left, double right)
{
    if(left < right)
        _fail(file,line, "%f is not greater than %f", left, right);
}

/* string checks */
void _check_equal_string(const char* file, int line, const char* expected, const char* actual)
{
    if(strcmp(expected, actual) != 0)
        _fail(file,line, "Expected: %s  Actual: %s", expected, actual);
}
void _check_not_equal_string(const char* file, int line, const char* expected, const char* actual)
{
    if(strcmp(expected, actual) == 0)
        _fail(file,line, "Strings are equal: %s", actual);
}


int _register_test(test_func_t* func)
{
    _test_funcs[_num_tests] = func;
    return _num_tests++;
}
void _ignore_test(void)
{
    _current_result = kResultIgnore;
}

int run_all_tests(int argc, const char* argv[])
{
    int ii;
    printf("----------------------------------------\n");
    for(ii=0;ii<_num_tests;++ii) {
        _current_result = kResultPass;
        _test_funcs[ii]();
        switch(_current_result)
        {
        case kResultPass: _num_tests_passed++; printf("."); break;
        case kResultFail: _num_tests_failed++; break;
        case kResultIgnore: _num_tests_ignored++; printf("!"); break;
        }
    }
    printf("\n----------------------------------------\n");
    printf("%d failed, %d passed, %d ignored, %d total\n",
            _num_tests_failed, _num_tests_passed, _num_tests_ignored, _num_tests);

    return _num_tests_failed;
    (void)sizeof(argc);
    (void)sizeof(*argv);
}
