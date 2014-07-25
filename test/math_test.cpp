/** @file math_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "vec_math.h"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

namespace {

static float _rand_float(float min, float max)
{
    float f = rand()/(float)RAND_MAX;
    f *= (max-min);
    return f+min;
}


TEST(Sphere, SpherePlaneCollision)
{
    Vec3 pt = {
        _rand_float( -50.0f, 50.0f ),
        _rand_float( -50.0f, 50.0f ),
        _rand_float( -50.0f, 50.0f )
    };
    Vec3 n = {
        _rand_float( -50.0f, 50.0f ),
        _rand_float( -50.0f, 50.0f ),
        _rand_float( -50.0f, 50.0f )
    };
    Plane p = plane_from_point_normal(pt, n);
    Sphere s = { { 0.0f, 0.0f, 0.0f }, 0.0f };

    n = vec3_normalize(n);
    p = plane_from_point_normal(pt, n);

    /* Sphere on plane */
    s.center = pt;
    s.radius = 1.0f;
    EXPECT_TRUE(0 != sphere_plane_intersect(p, s));
    
    /* Sphere above plane, touching */
    s.center = vec3_add(pt, n);
    s.radius = 2.0f;
    EXPECT_TRUE(0 != sphere_plane_intersect(p, s));
    
    /* Sphere above plane, not touching */
    s.center = vec3_add(pt, n);
    s.radius = 0.5f;
    EXPECT_FALSE(sphere_plane_intersect(p, s));
    
    /* Sphere below plane, touching */
    s.center = vec3_sub(pt, n);
    s.radius = 2.0f;
    EXPECT_TRUE(0 != sphere_plane_intersect(p, s));
    
    /* Sphere below plane, not touching */
    s.center = vec3_sub(pt, n);
    s.radius = 0.5f;
    EXPECT_FALSE(sphere_plane_intersect(p, s));
}

}
