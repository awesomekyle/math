/** @file math_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

#include "vec_math.h"
#include "glm/glm.hpp"

#define CHECK_EQUAL_VEC2(a,b) \
    CHECK_EQUAL_FLOAT((a)[0], (b)[0]); \
    CHECK_EQUAL_FLOAT((a)[1], (b)[1])

namespace
{

float _rand_float(float min, float max)
{
    float f = rand()/(float)RAND_MAX;
    f *= (max-min);
    return f-min;
}

struct Vec2Fixture
{
    glm::vec2   a,b,c;
    Vec2        i,j,k;
    float       s;

    Vec2Fixture()
    {
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a + 2*3;
        while(_a != end) {
            *_b = *_a = _rand_float(-100.0f, 100.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-100.0f, 100.0f);
    }
    ~Vec2Fixture() { }
};

TEST_FIXTURE(Vec2Fixture, Vec2Add)
{
    a = b+c;
    i = vec2_add(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Sub)
{
    a = b-c;
    i = vec2_sub(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Mul)
{
    a = b*c;
    i = vec2_mul(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Div)
{
    a = b/c;
    i = vec2_div(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}

TEST_FIXTURE(Vec2Fixture, Vec2AddScalar)
{
    a = b+s;
    i = vec2_add_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2SubScalar)
{
    a = b-s;
    i = vec2_sub_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2MulScalar)
{
    a = b*s;
    i = vec2_mul_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2DivScalar)
{
    a = b/s;
    i = vec2_div_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Hadd)
{
    float expected = a.x+a.y;
    float actual = vec2_hadd(i);
    CHECK_EQUAL_FLOAT(expected, actual);
}
TEST_FIXTURE(Vec2Fixture, Vec2Equal)
{
    CHECK_TRUE(vec2_equal(j, j));
    CHECK_FALSE(vec2_equal(j, k));
}
TEST_FIXTURE(Vec2Fixture, Vec2Length)
{
    CHECK_EQUAL_FLOAT(glm::length(a), vec2_length(i));
}
TEST_FIXTURE(Vec2Fixture, Vec2Distance)
{
    CHECK_EQUAL_FLOAT(glm::distance(a,b), vec2_distance(i,j));
    CHECK_EQUAL_FLOAT(vec2_distance(j,i), vec2_distance(i,j));
}
TEST_FIXTURE(Vec2Fixture, Vec2Normalize)
{
    a = glm::normalize(a);
    i = vec2_normalize(i);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2MinMax)
{
    a = glm::max(b, c);
    i = vec2_max(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec2_min(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Lerp)
{
}

} // anonymous namespace
