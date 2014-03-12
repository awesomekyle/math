/** @file math_test_c.c
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"
#include <stdlib.h>
#include "vec_math.h"

#ifdef _MSC_VER
    #pragma warning(disable:4204) /* non-constant aggregate initializer */
#endif

static float _rand_float(float min, float max)
{
    float f = rand()/(float)RAND_MAX;
    f *= (max-min);
    return f-min;
}

TEST(Vec2Add)
{
    Vec2 a = { 32.45f, -1083.82f };
    Vec2 b = { -32.45f, 1083.82f };
    Vec2 c = vec2_add(a, b);
    CHECK_EQUAL_FLOAT(0.0f, c.x);
    CHECK_EQUAL_FLOAT(0.0f, c.y);
}

TEST(SpherePlaneCollision)
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
    Sphere s = {0.0f};

    n = vec3_normalize(n);
    p = plane_from_point_normal(pt, n);

    /* Sphere on plane */
    s.center = pt;
    s.radius = 1.0f;
    CHECK_TRUE(sphere_plane_intersect(p, s));
    
    /* Sphere above plane, touching */
    s.center = vec3_add(pt, n);
    s.radius = 2.0f;
    CHECK_TRUE(sphere_plane_intersect(p, s));
    
    /* Sphere above plane, not touching */
    s.center = vec3_add(pt, n);
    s.radius = 0.5f;
    CHECK_FALSE(sphere_plane_intersect(p, s));
    
    /* Sphere below plane, touching */
    s.center = vec3_sub(pt, n);
    s.radius = 2.0f;
    CHECK_TRUE(sphere_plane_intersect(p, s));
    
    /* Sphere below plane, not touching */
    s.center = vec3_sub(pt, n);
    s.radius = 0.5f;
    CHECK_FALSE(sphere_plane_intersect(p, s));
}

TEST_MODULE(math)
{
    REGISTER_TEST(Vec2Add);
    REGISTER_TEST(SpherePlaneCollision);
}
