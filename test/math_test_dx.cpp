/** @file math_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

#include "vec_math.h"

#include <stdlib.h>
#include <immintrin.h>
#define _XM_NO_INTRINSICS_
#include <DirectXMath.h>
using namespace DirectX;

#define CHECK_EQUAL_VEC2(a,b) \
    CHECK_EQUAL_FLOAT((a)[0], (b)[0]); \
    CHECK_EQUAL_FLOAT((a)[1], (b)[1])

#define CHECK_EQUAL_VEC3(a,b) \
    CHECK_EQUAL_FLOAT((a)[0], (b)[0]); \
    CHECK_EQUAL_FLOAT((a)[1], (b)[1]); \
    CHECK_EQUAL_FLOAT((a)[2], (b)[2])

#define CHECK_EQUAL_VEC4(a,b) \
    CHECK_EQUAL_FLOAT((a)[0], (b)[0]); \
    CHECK_EQUAL_FLOAT((a)[1], (b)[1]); \
    CHECK_EQUAL_FLOAT((a)[2], (b)[2]); \
    CHECK_EQUAL_FLOAT((a)[3], (b)[3])

#define CHECK_EQUAL_MAT3(expected, actual)  \
    XMFLOAT3X3 _m;                           \
    XMStoreFloat3x3(&_m, *((XMMATRIX*)expected));          \
    float* _t = (float*)&_m;                         \
    for(int ii=0;ii<9;++ii) {                   \
        CHECK_EQUAL_FLOAT((_t)[ii], (actual)[ii]);    \
    }

#define CHECK_EQUAL_MAT4(expected, actual)  \
    for(int ii=0;ii<16;++ii) {                   \
        CHECK_EQUAL_FLOAT((expected)[ii], (actual)[ii]);    \
    }

namespace
{
#ifndef _XM_NO_INTRINSICS_
    float XMVectorHadd(XMVECTOR v) { v = _mm_hadd_ps(v,v); v = _mm_hadd_ps(v,v); return v.m128_f32[1]; }
#else
    float XMVectorHadd(XMVECTOR v1) { __m128 v = _mm_load_ps(v1.vector4_f32); v = _mm_hadd_ps(v,v); v = _mm_hadd_ps(v,v); return v.m128_f32[1]; }
#endif

float _rand_float(float min, float max)
{
    float f = rand()/(float)RAND_MAX;
    f *= (max-min);
    return f-min;
}

/******************************************************************************\
 * Vec2                                                                       *
\******************************************************************************/
struct Vec2Fixture
{
    DirectX::XMVECTOR    a,b,c;
    Vec2        i,j,k;
    float       s,s2,s3,s4;

    Vec2Fixture()
    {
        memset(&a, 0, sizeof(DirectX::XMVECTOR)*3);
        int count = 0;
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a +  sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
            if(++count % 2 == 0)
                ++_a, ++_a;
        }
        s = s2 = s3 = s4 = _rand_float(-50.0f, 50.0f);
    }
    ~Vec2Fixture() { }
};
TEST_FIXTURE(Vec2Fixture, Vec2Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,0,0);
    i = vec2_create(x,y);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Zero)
{
    a = XMVectorZero();
    i = vec2_zero;
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
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
    a = b + XMVectorSet(s,s,s,s);
    i = vec2_add_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
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
    float expected = XMVectorHadd(a);
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
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector2Length(a)), vec2_length(i));
}
TEST_FIXTURE(Vec2Fixture, Vec2Distance)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector2Length(a-b)), vec2_distance(i,j));
    CHECK_EQUAL_FLOAT(vec2_distance(j,i), vec2_distance(i,j));
}
TEST_FIXTURE(Vec2Fixture, Vec2Normalize)
{
    a = XMVector2Normalize(a);
    i = vec2_normalize(i);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2MinMax)
{
    a = XMVectorMax(b, c);
    i = vec2_max(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec2_min(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec2_lerp(j,k,f);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Negate)
{
    a = -b;
    i = vec2_negate(j);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}



/******************************************************************************\
 * Vec3                                                                       *
\******************************************************************************/
struct Vec3Fixture
{
    DirectX::XMVECTOR    a,b,c;
    Vec3        i,j,k;
    float       s,s2,s3,s4;

    Vec3Fixture()
    {
        memset(&a, 0, sizeof(DirectX::XMVECTOR)*3);
        int count = 0;
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a +  sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
            if(++count % 3 == 0)
                ++_a;
        }
        s = s2 = s3 = s4 = _rand_float(-50.0f, 50.0f);
    }
    ~Vec3Fixture() { }
};
TEST_FIXTURE(Vec3Fixture, Vec3Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,0);
    i = vec3_create(x,y,z);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Zero)
{
    a = XMVectorZero();
    i = vec3_zero;
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Add)
{
    a = b+c;
    i = vec3_add(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Sub)
{
    a = b-c;
    i = vec3_sub(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Mul)
{
    a = b*c;
    i = vec3_mul(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Div)
{
    a = b/c;
    i = vec3_div(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}

TEST_FIXTURE(Vec3Fixture, Vec3AddScalar)
{
    a = b + XMVectorSet(s,s,s,s);
    i = vec3_add_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
    i = vec3_sub_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3MulScalar)
{
    a = b*s;
    i = vec3_mul_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3DivScalar)
{
    a = b/s;
    i = vec3_div_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Hadd)
{
    float expected = XMVectorHadd(a);
    float actual = vec3_hadd(i);
    CHECK_EQUAL_FLOAT(expected, actual);
}
TEST_FIXTURE(Vec3Fixture, Vec3Equal)
{
    CHECK_TRUE(vec3_equal(j, j));
    CHECK_FALSE(vec3_equal(j, k));
}
TEST_FIXTURE(Vec3Fixture, Vec3Length)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector3Length(a)), vec3_length(i));
}
TEST_FIXTURE(Vec3Fixture, Vec3Distance)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector3Length(a-b)), vec3_distance(i,j));
    CHECK_EQUAL_FLOAT(vec3_distance(j,i), vec3_distance(i,j));
}
TEST_FIXTURE(Vec3Fixture, Vec3Normalize)
{
    a = XMVector3Normalize(a);
    i = vec3_normalize(i);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3MinMax)
{
    a = XMVectorMax(b, c);
    i = vec3_max(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec3_min(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec3_lerp(j,k,f);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Negate)
{
    a = -b;
    i = vec3_negate(j);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Dot)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector3Dot(a,b)), vec3_dot(i,j));
}
TEST_FIXTURE(Vec3Fixture, Vec3Cross)
{
    a = XMVector3Cross(b,c);
    i = vec3_cross(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Vec4                                                                       *
\******************************************************************************/
struct Vec4Fixture
{
    DirectX::XMVECTOR    a,b,c;
    Vec4        i,j,k;
    float       s,s2,s3,s4;

    Vec4Fixture()
    {
        memset(&a, 0, sizeof(DirectX::XMVECTOR)*3);
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a +  sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
        }
        s = s2 = s3 = s4 = _rand_float(-50.0f, 50.0f);
    }
    ~Vec4Fixture() { }
};
TEST_FIXTURE(Vec4Fixture, Vec4Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f),
          w = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,w);
    i = vec4_create(x,y,z,w);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Zero)
{
    a = XMVectorZero();
    i = vec4_zero;
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Add)
{
    a = b+c;
    i = vec4_add(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Sub)
{
    a = b-c;
    i = vec4_sub(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Mul)
{
    a = b*c;
    i = vec4_mul(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Div)
{
    a = b/c;
    i = vec4_div(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}

TEST_FIXTURE(Vec4Fixture, Vec4AddScalar)
{
    a = b + XMVectorSet(s,s,s,s);
    i = vec4_add_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
    i = vec4_sub_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4MulScalar)
{
    a = b*s;
    i = vec4_mul_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4DivScalar)
{
    a = b/s;
    i = vec4_div_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Hadd)
{
    float expected = XMVectorHadd(a);
    float actual = vec4_hadd(i);
    CHECK_EQUAL_FLOAT(expected, actual);
}
TEST_FIXTURE(Vec4Fixture, Vec4Equal)
{
    CHECK_TRUE(vec4_equal(j, j));
    CHECK_FALSE(vec4_equal(j, k));
}
TEST_FIXTURE(Vec4Fixture, Vec4Length)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector4Length(a)), vec4_length(i));
}
TEST_FIXTURE(Vec4Fixture, Vec4Distance)
{
    CHECK_EQUAL_FLOAT(XMVectorGetX(XMVector4Length(a-b)), vec4_distance(i,j));
    CHECK_EQUAL_FLOAT(vec4_distance(j,i), vec4_distance(i,j));
}
TEST_FIXTURE(Vec4Fixture, Vec4Normalize)
{
    a = XMVector4Normalize(a);
    i = vec4_normalize(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4MinMax)
{
    a = XMVectorMax(b, c);
    i = vec4_max(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec4_min(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec4_lerp(j,k,f);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Negate)
{
    a = -b;
    i = vec4_negate(j);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
struct Mat3Fixture
{
    XMMATRIX    a,b,c;
    Mat3        i,j,k;
    float       s;

    Mat3Fixture()
    {
        a = b = c = XMMatrixIdentity();
        memset(&i, 0, sizeof(i)*3);
        int count = 0;
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a + sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
            if(++count % 3 == 0)
                ++_a;
            if(count % 9 == 0)
                _a += 4;
        }
        s = _rand_float(-50.0f, 50.0f);
    }
    ~Mat3Fixture() { }
};
TEST_FIXTURE(Mat3Fixture, Mat3Identity)
{
    a = XMMatrixIdentity();
    i = mat3_identity;
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Scale)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMMatrixScaling(x,y,z);
    i = mat3_scalef(x,y,z);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateX)
{
    a = XMMatrixRotationX(s);
    i = mat3_rotation_x(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateY)
{
    a = XMMatrixRotationY(s);
    i = mat3_rotation_y(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateZ)
{
    a = XMMatrixRotationZ(s);
    i = mat3_rotation_z(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Rotate)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMMatrixRotationAxis(XMVectorSet(x,y,z,0.0f), s);
    i = mat3_rotation_axis(vec3_create(x,y,z), s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Multiply)
{
    a = b*c;
    i = mat3_multiply(j,k);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Determinant)
{
    CHECK_EQUAL_FLOAT_EPSILON(XMVectorGetX(XMMatrixDeterminant(a)), mat3_determinant(i), 0.5);
}
TEST_FIXTURE(Mat3Fixture, Mat3Transpose)
{
    a = XMMatrixTranspose(a);
    i = mat3_transpose(i);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Inverse)
{
    a = XMMatrixInverse(NULL, a);
    i = mat3_inverse(i);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3MultiplyScalar)
{
    a = a * s;
    i = mat3_mul_scalar(i, s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3MultiplyVector)
{
    float x = _rand_float(-25.0f, 25.0f),
          y = _rand_float(-25.0f, 25.0f),
          z = _rand_float(-25.0f, 25.0f);
    XMVECTOR u = XMVectorSet(x,y,z,0);
    Vec3 v = vec3_create(x,y,z);

    a = XMMatrixTranspose(a);
    u = XMVector3Transform(u, a);
    v = mat3_mul_vector(v, i);
    CHECK_EQUAL_VEC3((float*)&u, (float*)&v);
}


/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
struct Mat4Fixture
{
    XMMATRIX    a,b,c;
    Mat4        i,j,k;
    float       s;

    Mat4Fixture()
    {
        a = b = c = XMMatrixIdentity();
        memset(&i, 0, sizeof(i)*3);
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a + sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-25.0f, 25.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-25.0f, 25.0f);
    }
    ~Mat4Fixture() { }
};
TEST_FIXTURE(Mat4Fixture, Mat4Identity)
{
    a = XMMatrixIdentity();
    i = mat4_identity;
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4Scale)
{
    float x = _rand_float(0.1f, 25.0f),
          y = _rand_float(0.1f, 25.0f),
          z = _rand_float(0.1f, 25.0f);
    a = XMMatrixScaling(x,y,z);
    i = mat4_scalef(x,y,z);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4RotateX)
{
    a = XMMatrixRotationX(s);
    i = mat4_rotation_x(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4RotateY)
{
    a = XMMatrixRotationY(s);
    i = mat4_rotation_y(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4RotateZ)
{
    a = XMMatrixRotationZ(s);
    i = mat4_rotation_z(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4Rotate)
{
    float x = _rand_float(0.1f, 25.0f),
          y = _rand_float(0.1f, 25.0f),
          z = _rand_float(0.1f, 25.0f);
    a = XMMatrixRotationAxis(XMVectorSet(x,y,z,0.0f), s);
    i = mat4_rotation_axis(vec3_create(x,y,z), s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4Multiply)
{
    a = b*c;
    i = mat4_multiply(j,k);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4Determinant)
{
    CHECK_EQUAL_FLOAT_EPSILON(XMVectorGetX(XMMatrixDeterminant(a)), mat4_determinant(i), 0.5);
}
TEST_FIXTURE(Mat4Fixture, Mat4Transpose)
{
    a = XMMatrixTranspose(a);
    i = mat4_transpose(i);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4Inverse)
{
    a = XMMatrixInverse(NULL, a);
    i = mat4_inverse(i);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4MultiplyScalar)
{
    a = a * s;
    i = mat4_mul_scalar(i, s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat4Fixture, Mat4MultiplyVector)
{
    float x = _rand_float(-25.0f, 25.0f),
          y = _rand_float(-25.0f, 25.0f),
          z = _rand_float(-25.0f, 25.0f),
          w = _rand_float(-25.0f, 25.0f);
    XMVECTOR u = XMVectorSet(x,y,z,w);
    Vec4 v = vec4_create(x,y,z,w);

    a = XMMatrixTranspose(a);
    u = XMVector4Transform(u, a);
    v = mat4_mul_vector(v, i);
    CHECK_EQUAL_VEC4((float*)&u, (float*)&v);
}


/******************************************************************************\
 * Quaternion                                                                  *
\******************************************************************************/
struct QuaternionFixture
{
    XMVECTOR    a,b,c;
    Quaternion  i,j,k;
    float       s;

    QuaternionFixture()
    {
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a +  sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-50.0f, 50.0f);
    }
    ~QuaternionFixture() { }
};
TEST_FIXTURE(QuaternionFixture, CreateAxisAngle)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMQuaternionRotationAxis(XMVectorSet(x,y,z,0), s);
    i = quat_from_axis_anglef(x,y,z,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(QuaternionFixture, CreateEuler)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f);
    a = XMQuaternionRotationRollPitchYaw(x,y,z);
    a = XMQuaternionNormalize(a);
    i = quat_from_euler(x,y,z);
    //CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
    // TODO: Change the order in `quat_from_euler`
}
TEST_FIXTURE(QuaternionFixture, Normalize)
{
    a = XMQuaternionNormalize(a);
    i = quat_normalize(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(QuaternionFixture, ConvertToMatrix)
{
    a = XMQuaternionNormalize(a);
    XMMATRIX x = XMMatrixRotationQuaternion(a);
    Mat3 y = quat_to_mat3(i);
    CHECK_EQUAL_MAT3((float*)&x, (float*)&y);
}
TEST_FIXTURE(QuaternionFixture, Conjugate)
{
    a = XMQuaternionConjugate(a);
    i = quat_conjugate(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(QuaternionFixture, Inverse)
{
    a = XMQuaternionNormalize(a);
    a = XMQuaternionInverse(a);
    i = quat_inverse(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(QuaternionFixture, Multiply)
{
    a = XMQuaternionMultiply(b,c);
    i = quat_multiply(j, k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Transform                                                                  *
\******************************************************************************/
TEST(TransformToMatrix)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f);
    float s = _rand_float(0.1f, 50.0f);
    float rx = _rand_float(-50.0f, 50.0f),
          ry = _rand_float(-50.0f, 50.0f),
          rz = _rand_float(-50.0f, 50.0f);
    float r = _rand_float(-50.0f, 50.0f);

    XMMATRIX a = XMMatrixAffineTransformation(XMVectorSet(s,s,s,0), 
                                              XMVectorZero(), 
                                              XMQuaternionRotationAxis(XMVectorSet(rx,ry,rz,0), r),
                                              XMVectorSet(x,y,z,0));

    Transform t = { quat_from_axis_anglef(rx, ry, rz, r), vec3_create(x,y,z), s };
    Mat4 i = transform_get_matrix(t);

    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}

} // anonymous namespace
