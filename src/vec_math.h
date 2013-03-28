/** @file vec_math.h
 *  @brief 3D Linear math library
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#ifndef __vec_math_h__
#define __vec_math_h__
#include <math.h>

/**
 * Types
 */
typedef struct Vec2
{
    float x, y;
} Vec2;

/**
 * Constants
 */
static const float kEpsilon  = 0.00001f;
static const float kPi       = 3.141592653589793238462643383280f;
static const float k2Pi      = 6.283185307179586476925286766559f;
static const float kPiDiv2   = 1.570796326794896619231321691640f;
static const float kInvPi    = 0.318309886183790671537767526745f;
static const float kDegToRad = 0.017453292519943295769236907685f;
static const float kRadToDeg = 57.29577951308232087679815481410f;

#ifdef __cplusplus
extern "C" { // C linkage
    typedef const Vec2& VEC2_INPUT;
    #define INLINE inline
#else
    typedef Vec2 VEC2_INPUT;
    #define INLINE static __inline
#endif

/******************************************************************************\
 * Vec2                                                                       *
\******************************************************************************/
/* Basic aritmatic */
INLINE Vec2 vec2_add(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}
INLINE Vec2 vec2_sub(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    return res;
}
INLINE Vec2 vec2_mul(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    return res;
}
INLINE Vec2 vec2_div(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    return res;
}

/* Scalar math */
INLINE Vec2 vec2_add_scalar(VEC2_INPUT v, float f)
{
    Vec2 res;
    res.x = v.x + f;
    res.y = v.y + f;
    return res;
}
INLINE Vec2 vec2_sub_scalar(VEC2_INPUT v, float f)
{
    Vec2 res;
    res.x = v.x - f;
    res.y = v.y - f;
    return res;
}
INLINE Vec2 vec2_mul_scalar(VEC2_INPUT v, float f)
{
    Vec2 res;
    res.x = v.x * f;
    res.y = v.y * f;
    return res;
}
INLINE Vec2 vec2_div_scalar(VEC2_INPUT v, float f)
{
    Vec2 res;
    res.x = v.x / f;
    res.y = v.y / f;
    return res;
}
/* Misc */
INLINE float vec2_hadd(VEC2_INPUT v)
{
    return v.x+v.y;
}
INLINE int vec2_equal(VEC2_INPUT a, VEC2_INPUT b)
{
    return fabsf(a.x - b.x) < kEpsilon &&
           fabsf(a.y - b.y) < kEpsilon;
}
INLINE int vec2_equal_scalar(VEC2_INPUT v, float f)
{
    return fabsf(v.x - f) < kEpsilon &&
           fabsf(v.y - f) < kEpsilon;
}
INLINE float vec2_length_sq(VEC2_INPUT v)
{
    return v.x*v.x + v.y*v.y;
}
INLINE float vec2_length(VEC2_INPUT v)
{
    return sqrtf(vec2_length_sq(v));
}
INLINE float vec2_distance_sq(VEC2_INPUT a, VEC2_INPUT b)
{
    return vec2_length_sq(vec2_sub(a,b));
}
INLINE float vec2_distance(VEC2_INPUT a, VEC2_INPUT b)
{
    return sqrtf(vec2_distance_sq(a,b));
}
INLINE Vec2 vec2_normalize(VEC2_INPUT v)
{
    return vec2_div_scalar(v,vec2_length(v));
}
INLINE Vec2 vec2_min(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 v;
    v.x = fminf(a.x, b.x);
    v.y = fminf(a.y, b.y);
    return v;
}
INLINE Vec2 vec2_max(VEC2_INPUT a, VEC2_INPUT b)
{
    Vec2 v;
    v.x = fmaxf(a.x, b.x);
    v.y = fmaxf(a.y, b.y);
    return v;
}

#ifdef __cplusplus
} // extern "C" {
#endif

#endif /* include guard */
