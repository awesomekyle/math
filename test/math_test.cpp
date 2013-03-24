/** @file math_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

#include "vec_math.h"

TEST(Vec2Add)
{
    Vec2 a = { 32.45f, -1083.82f };
    Vec2 b = { -32.45f, 1083.82f };
    Vec2 c = vec2_add(a, b);
    CHECK_EQUAL_FLOAT(0.0f, c.x);
    CHECK_EQUAL_FLOAT(0.0f, c.y);
}
