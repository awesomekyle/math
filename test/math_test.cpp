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
            *_b = *_a = _rand_float(-500.0f, 500.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-500.0f, 500.0f);
    }
    ~Vec2Fixture() { }
};

TEST_FIXTURE(Vec2Fixture, Vec2Add)
{
    a = b+c;
    i = vec2_add(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}

} // anonymous namespace
