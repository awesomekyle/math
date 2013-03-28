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
typedef struct Vec3
{
    float x, y, z;
} Vec3;
typedef struct Vec4
{
    float x, y, z, w;
} Vec4;
typedef struct Mat3
{
    Vec3 r0, r1, r2;
} Mat3;

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
    typedef const Vec3& VEC3_INPUT;
    typedef const Vec4& VEC4_INPUT;
    typedef const Mat3& MAT3_INPUT;
    #define INLINE inline
#else
    typedef Vec2 VEC2_INPUT;
    typedef Vec3 VEC3_INPUT;
    typedef Vec4 VEC4_INPUT;
    typedef Mat3 MAT3_INPUT;
    #define INLINE static __inline
#endif

/******************************************************************************\
 * Vec2                                                                       *
\******************************************************************************/
static const Vec2 vec2_zero = {0.0f,0.0f};
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
INLINE Vec2 vec2_lerp(VEC2_INPUT a, VEC2_INPUT b, float t)
{
    Vec2 d = vec2_sub(b, a);
    Vec2 tt = vec2_mul_scalar(d, t);
    return vec2_add(a, tt);
}
INLINE Vec2 vec2_negate(VEC2_INPUT v)
{
    Vec2 r;
    r.x = -v.x;
    r.y = -v.y;
    return r;
}


/******************************************************************************\
 * Vec3                                                                       *
\******************************************************************************/
static const Vec3 vec3_zero = {0.0f,0.0f,0.0f};
/* Basic aritmatic */
INLINE Vec3 vec3_add(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return res;
}
INLINE Vec3 vec3_sub(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return res;
}
INLINE Vec3 vec3_mul(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    return res;
}
INLINE Vec3 vec3_div(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    return res;
}

/* Scalar math */
INLINE Vec3 vec3_add_scalar(VEC3_INPUT v, float f)
{
    Vec3 res;
    res.x = v.x + f;
    res.y = v.y + f;
    res.z = v.z + f;
    return res;
}
INLINE Vec3 vec3_sub_scalar(VEC3_INPUT v, float f)
{
    Vec3 res;
    res.x = v.x - f;
    res.y = v.y - f;
    res.z = v.z - f;
    return res;
}
INLINE Vec3 vec3_mul_scalar(VEC3_INPUT v, float f)
{
    Vec3 res;
    res.x = v.x * f;
    res.y = v.y * f;
    res.z = v.z * f;
    return res;
}
INLINE Vec3 vec3_div_scalar(VEC3_INPUT v, float f)
{
    Vec3 res;
    res.x = v.x / f;
    res.y = v.y / f;
    res.z = v.z / f;
    return res;
}
/* Misc */
INLINE float vec3_hadd(VEC3_INPUT v)
{
    return v.x + v.y + v.z;
}
INLINE int vec3_equal(VEC3_INPUT a, VEC3_INPUT b)
{
    return fabsf(a.x - b.x) < kEpsilon &&
           fabsf(a.y - b.y) < kEpsilon &&
           fabsf(a.z - b.z) < kEpsilon;
}
INLINE int vec3_equal_scalar(VEC3_INPUT v, float f)
{
    return fabsf(v.x - f) < kEpsilon &&
           fabsf(v.y - f) < kEpsilon &&
           fabsf(v.z - f) < kEpsilon;
}
INLINE float vec3_length_sq(VEC3_INPUT v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z;
}
INLINE float vec3_length(VEC3_INPUT v)
{
    return sqrtf(vec3_length_sq(v));
}
INLINE float vec3_distance_sq(VEC3_INPUT a, VEC3_INPUT b)
{
    return vec3_length_sq(vec3_sub(a,b));
}
INLINE float vec3_distance(VEC3_INPUT a, VEC3_INPUT b)
{
    return sqrtf(vec3_distance_sq(a,b));
}
INLINE Vec3 vec3_normalize(VEC3_INPUT v)
{
    return vec3_div_scalar(v,vec3_length(v));
}
INLINE Vec3 vec3_min(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 v;
    v.x = fminf(a.x, b.x);
    v.y = fminf(a.y, b.y);
    v.z = fminf(a.z, b.z);
    return v;
}
INLINE Vec3 vec3_max(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 v;
    v.x = fmaxf(a.x, b.x);
    v.y = fmaxf(a.y, b.y);
    v.z = fmaxf(a.z, b.z);
    return v;
}
INLINE Vec3 vec3_lerp(VEC3_INPUT a, VEC3_INPUT b, float t)
{
    Vec3 d = vec3_sub(b, a);
    Vec3 tt = vec3_mul_scalar(d, t);
    return vec3_add(a, tt);
}
INLINE Vec3 vec3_negate(VEC3_INPUT v)
{
    Vec3 r;
    r.x = -v.x;
    r.y = -v.y;
    r.z = -v.z;
    return r;
}
INLINE float vec3_dot(VEC3_INPUT a, VEC3_INPUT b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
INLINE Vec3 vec3_cross(VEC3_INPUT a, VEC3_INPUT b)
{
    Vec3 r;
    r.x = a.y*b.z - a.z*b.y;
    r.y = a.z*b.x - a.x*b.z;
    r.z = a.x*b.y - a.y*b.x;
    return r;
}



/******************************************************************************\
 * Vec4                                                                       *
\******************************************************************************/
static const Vec4 vec4_zero = {0.0f,0.0f,0.0f,0.0f};
/* Basic aritmatic */
INLINE Vec4 vec4_add(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.w = a.w + b.w;
    return res;
}
INLINE Vec4 vec4_sub(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.w = a.w - b.w;
    return res;
}
INLINE Vec4 vec4_mul(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    res.w = a.w * b.w;
    return res;
}
INLINE Vec4 vec4_div(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 res;
    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    res.w = a.w / b.w;
    return res;
}

/* Scalar math */
INLINE Vec4 vec4_add_scalar(VEC4_INPUT v, float f)
{
    Vec4 res;
    res.x = v.x + f;
    res.y = v.y + f;
    res.z = v.z + f;
    res.w = v.w + f;
    return res;
}
INLINE Vec4 vec4_sub_scalar(VEC4_INPUT v, float f)
{
    Vec4 res;
    res.x = v.x - f;
    res.y = v.y - f;
    res.z = v.z - f;
    res.w = v.w - f;
    return res;
}
INLINE Vec4 vec4_mul_scalar(VEC4_INPUT v, float f)
{
    Vec4 res;
    res.x = v.x * f;
    res.y = v.y * f;
    res.z = v.z * f;
    res.w = v.w * f;
    return res;
}
INLINE Vec4 vec4_div_scalar(VEC4_INPUT v, float f)
{
    Vec4 res;
    res.x = v.x / f;
    res.y = v.y / f;
    res.z = v.z / f;
    res.w = v.w / f;
    return res;
}
/* Misc */
INLINE float vec4_hadd(VEC4_INPUT v)
{
    return v.x + v.y + v.z + v.w;
}
INLINE int vec4_equal(VEC4_INPUT a, VEC4_INPUT b)
{
    return fabsf(a.x - b.x) < kEpsilon &&
           fabsf(a.y - b.y) < kEpsilon &&
           fabsf(a.z - b.z) < kEpsilon &&
           fabsf(a.w - b.w) < kEpsilon;
}
INLINE int vec4_equal_scalar(VEC4_INPUT v, float f)
{
    return fabsf(v.x - f) < kEpsilon &&
           fabsf(v.y - f) < kEpsilon &&
           fabsf(v.z - f) < kEpsilon &&
           fabsf(v.w - f) < kEpsilon;
}
INLINE float vec4_length_sq(VEC4_INPUT v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}
INLINE float vec4_length(VEC4_INPUT v)
{
    return sqrtf(vec4_length_sq(v));
}
INLINE float vec4_distance_sq(VEC4_INPUT a, VEC4_INPUT b)
{
    return vec4_length_sq(vec4_sub(a,b));
}
INLINE float vec4_distance(VEC4_INPUT a, VEC4_INPUT b)
{
    return sqrtf(vec4_distance_sq(a,b));
}
INLINE Vec4 vec4_normalize(VEC4_INPUT v)
{
    return vec4_div_scalar(v,vec4_length(v));
}
INLINE Vec4 vec4_min(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 v;
    v.x = fminf(a.x, b.x);
    v.y = fminf(a.y, b.y);
    v.z = fminf(a.z, b.z);
    v.w = fminf(a.w, b.w);
    return v;
}
INLINE Vec4 vec4_max(VEC4_INPUT a, VEC4_INPUT b)
{
    Vec4 v;
    v.x = fmaxf(a.x, b.x);
    v.y = fmaxf(a.y, b.y);
    v.z = fmaxf(a.z, b.z);
    v.w = fmaxf(a.w, b.w);
    return v;
}
INLINE Vec4 vec4_lerp(VEC4_INPUT a, VEC4_INPUT b, float t)
{
    Vec4 d = vec4_sub(b, a);
    Vec4 tt = vec4_mul_scalar(d, t);
    return vec4_add(a, tt);
}
INLINE Vec4 vec4_negate(VEC4_INPUT v)
{
    Vec4 r;
    r.x = -v.x;
    r.y = -v.y;
    r.z = -v.z;
    r.w = -v.w;
    return r;
}

/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
static const Mat3 mat3_identity = {
    { 1.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f },
};
INLINE Mat3 mat3_scale(float x, float y, float z)
{
    Mat3 r = mat3_identity;
    r.r0.x = x;
    r.r1.y = y;
    r.r2.z = z;
    return r;
}

#ifdef __cplusplus
} // extern "C" {
#endif

#endif /* include guard */
