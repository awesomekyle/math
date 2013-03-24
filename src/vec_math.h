/** @file vec_math.h
 *  @brief 3D Linear math library
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#ifndef __vec_math_h__
#define __vec_math_h__

typedef struct Vec2
{
    float x, y;
} Vec2;


#ifdef __cplusplus
extern "C" { // C linkage
    typedef const Vec2& VEC2_INPUT;
#else
    typedef Vec2 VEC2_INPUT;
#endif

Vec2 vec2_add(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}


#ifdef __cplusplus
} // extern "C" {
#endif

#endif /* include guard */
