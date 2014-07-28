/** @file math_test_dx.cpp
 *  @copyright Copyright (c) 2014 Kyle Weicht. All rights reserved.
 */
 #include "vec_math.h"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <stdlib.h>
#include <immintrin.h>
#define _XM_NO_INTRINSICS_
#include <DirectXMath.h>
using namespace DirectX;

#define EXPECT_VEC2_EQ(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f)

#define EXPECT_VEC3_EQ(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f); \
    EXPECT_NEAR((a)[2], (b)[2], 0.001f)

    
#define EXPECT_VEC4_EQ(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f); \
    EXPECT_NEAR((a)[2], (b)[2], 0.001f); \
    EXPECT_NEAR((a)[3], (b)[3], 0.001f)

#define EXPECT_MAT3_EQ(expected, actual)  \
    XMFLOAT3X3 _m;                           \
    XMStoreFloat3x3(&_m, *((XMMATRIX*)expected));          \
    float* _t = (float*)&_m;                         \
    for(int ii=0;ii<9;++ii) {                   \
        EXPECT_NEAR((_t)[ii], (actual)[ii], 0.001f);    \
    }

#define EXPECT_MAT4_EQ(expected, actual)  \
    for(int ii=0;ii<16;++ii) {                   \
        EXPECT_NEAR((expected)[ii], (actual)[ii], 0.001f);    \
    }

namespace DXTests
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
    return f+min;
}

class DXVec2Tests : public Test
{
protected:
    DXVec2Tests(){}
    ~DXVec2Tests(){}

    virtual void SetUp() {
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
    
    DirectX::XMVECTOR    a,b,c;
    Vec2        i,j,k;
    float       s,s2,s3,s4;
};
TEST_F(DXVec2Tests, Vec2Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,0,0);
    i = vec2_create(x,y);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Zero)
{
    a = XMVectorZero();
    i = vec2_zero;
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Add)
{
    a = b+c;
    i = vec2_add(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Sub)
{
    a = b-c;
    i = vec2_sub(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Mul)
{
    a = b*c;
    i = vec2_mul(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Div)
{
    a = b/c;
    i = vec2_div(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}

TEST_F(DXVec2Tests, Vec2AddScalar)
{
    a = b + XMVectorSet(s,s,s,s);
    i = vec2_add_scalar(j,s);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
    i = vec2_sub_scalar(j,s);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2MulScalar)
{
    a = b*s;
    i = vec2_mul_scalar(j,s);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2DivScalar)
{
    a = b/s;
    i = vec2_div_scalar(j,s);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Hadd)
{
    float expected = XMVectorHadd(a);
    float actual = vec2_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(DXVec2Tests, Vec2Equal)
{
    EXPECT_TRUE(0 != vec2_equal(j, j));
    EXPECT_FALSE(vec2_equal(j, k));
}
TEST_F(DXVec2Tests, Vec2Length)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector2Length(a)), vec2_length(i));
}
TEST_F(DXVec2Tests, Vec2Distance)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector2Length(a-b)), vec2_distance(i,j));
    EXPECT_FLOAT_EQ(vec2_distance(j,i), vec2_distance(i,j));
}
TEST_F(DXVec2Tests, Vec2Normalize)
{
    a = XMVector2Normalize(a);
    i = vec2_normalize(i);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2MinMax)
{
    a = XMVectorMax(b, c);
    i = vec2_max(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec2_min(j,k);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec2_lerp(j,k,f);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec2Tests, Vec2Negate)
{
    a = -b;
    i = vec2_negate(j);
    EXPECT_VEC2_EQ((float*)&a, (float*)&i);
}




/******************************************************************************\
 * Vec3                                                                       *
\******************************************************************************/
struct DXVec3Tests : public Test
{
    DirectX::XMVECTOR    a,b,c;
    Vec3        i,j,k;
    float       s,s2,s3,s4;

    virtual void SetUp()
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
};
TEST_F(DXVec3Tests, Vec3Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,0);
    i = vec3_create(x,y,z);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Zero)
{
    a = XMVectorZero();
    i = vec3_zero;
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Add)
{
    a = b+c;
    i = vec3_add(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Sub)
{
    a = b-c;
    i = vec3_sub(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Mul)
{
    a = b*c;
    i = vec3_mul(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Div)
{
    a = b/c;
    i = vec3_div(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}

TEST_F(DXVec3Tests, Vec3AddScalar)
{
    a = b + XMVectorSet(s,s,s,s);
    i = vec3_add_scalar(j,s);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
    i = vec3_sub_scalar(j,s);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3MulScalar)
{
    a = b*s;
    i = vec3_mul_scalar(j,s);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3DivScalar)
{
    a = b/s;
    i = vec3_div_scalar(j,s);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Hadd)
{
    float expected = XMVectorHadd(a);
    float actual = vec3_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(DXVec3Tests, Vec3Equal)
{
    EXPECT_TRUE(0 != vec3_equal(j, j));
    EXPECT_FALSE(vec3_equal(j, k));
}
TEST_F(DXVec3Tests, Vec3Length)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector3Length(a)), vec3_length(i));
}
TEST_F(DXVec3Tests, Vec3Distance)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector3Length(a-b)), vec3_distance(i,j));
    EXPECT_FLOAT_EQ(vec3_distance(j,i), vec3_distance(i,j));
}
TEST_F(DXVec3Tests, Vec3Normalize)
{
    a = XMVector3Normalize(a);
    i = vec3_normalize(i);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3MinMax)
{
    a = XMVectorMax(b, c);
    i = vec3_max(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec3_min(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec3_lerp(j,k,f);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Negate)
{
    a = -b;
    i = vec3_negate(j);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec3Tests, Vec3Dot)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector3Dot(a,b)), vec3_dot(i,j));
}
TEST_F(DXVec3Tests, Vec3Cross)
{
    a = XMVector3Cross(b,c);
    i = vec3_cross(j,k);
    EXPECT_VEC3_EQ((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Vec4                                                                       *
\******************************************************************************/
struct DXVec4Tests : public Test
{
    DirectX::XMVECTOR    a,b,c;
    Vec4        i,j,k;
    float       s,s2,s3,s4;

    virtual void SetUp()
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
};
TEST_F(DXVec4Tests, Vec4Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f),
          w = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,w);
    i = vec4_create(x,y,z,w);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Zero)
{
    a = XMVectorZero();
    i = vec4_zero;
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Add)
{
    a = b+c;
    i = vec4_add(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Sub)
{
    a = b-c;
    i = vec4_sub(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Mul)
{
    a = b*c;
    i = vec4_mul(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Div)
{
    a = b/c;
    i = vec4_div(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}

TEST_F(DXVec4Tests, Vec4AddScalar)
{
    a = b + XMVectorSet(s,s,s,s);
    i = vec4_add_scalar(j,s);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4SubScalar)
{
    a = b-XMVectorSet(s,s,s,s);
    i = vec4_sub_scalar(j,s);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4MulScalar)
{
    a = b*s;
    i = vec4_mul_scalar(j,s);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4DivScalar)
{
    a = b/s;
    i = vec4_div_scalar(j,s);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Hadd)
{
    float expected = XMVectorHadd(a);
    float actual = vec4_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(DXVec4Tests, Vec4Equal)
{
    EXPECT_TRUE(0 != vec4_equal(j, j));
    EXPECT_FALSE(vec4_equal(j, k));
}
TEST_F(DXVec4Tests, Vec4Length)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector4Length(a)), vec4_length(i));
}
TEST_F(DXVec4Tests, Vec4Distance)
{
    EXPECT_FLOAT_EQ(XMVectorGetX(XMVector4Length(a-b)), vec4_distance(i,j));
    EXPECT_FLOAT_EQ(vec4_distance(j,i), vec4_distance(i,j));
}
TEST_F(DXVec4Tests, Vec4Normalize)
{
    a = XMVector4Normalize(a);
    i = vec4_normalize(i);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4MinMax)
{
    a = XMVectorMax(b, c);
    i = vec4_max(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
    a = XMVectorMin(b, c);
    i = vec4_min(j,k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = XMVectorLerp(b,c,f);
    i = vec4_lerp(j,k,f);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXVec4Tests, Vec4Negate)
{
    a = -b;
    i = vec4_negate(j);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
struct DXMat3Tests : public Test
{
    XMMATRIX    a,b,c;
    Mat3        i,j,k;
    float       s;

    virtual void SetUp()
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
};
TEST_F(DXMat3Tests, Mat3Identity)
{
    a = XMMatrixIdentity();
    i = mat3_identity;
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3Scale)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMMatrixScaling(x,y,z);
    i = mat3_scalef(x,y,z);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3RotateX)
{
    a = XMMatrixRotationX(s);
    i = mat3_rotation_x(s);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3RotateY)
{
    a = XMMatrixRotationY(s);
    i = mat3_rotation_y(s);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3RotateZ)
{
    a = XMMatrixRotationZ(s);
    i = mat3_rotation_z(s);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3Rotate)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMMatrixRotationAxis(XMVectorSet(x,y,z,0.0f), s);
    i = mat3_rotation_axis(vec3_create(x,y,z), s);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3Multiply)
{
    a = b*c;
    i = mat3_multiply(j,k);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3Determinant)
{
    EXPECT_NEAR(XMVectorGetX(XMMatrixDeterminant(a)), mat3_determinant(i), 0.5);
}
TEST_F(DXMat3Tests, Mat3Transpose)
{
    a = XMMatrixTranspose(a);
    i = mat3_transpose(i);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3Inverse)
{
    a = XMMatrixInverse(NULL, a);
    i = mat3_inverse(i);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3MultiplyScalar)
{
    a = a * s;
    i = mat3_mul_scalar(i, s);
    EXPECT_MAT3_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat3Tests, Mat3MultiplyVector)
{
    float x = _rand_float(-25.0f, 25.0f),
          y = _rand_float(-25.0f, 25.0f),
          z = _rand_float(-25.0f, 25.0f);
    XMVECTOR u = XMVectorSet(x,y,z,0);
    Vec3 v = vec3_create(x,y,z);

    u = XMVector3Transform(u, a);
    v = mat3_mul_vector(v, i);
    EXPECT_VEC3_EQ((float*)&u, (float*)&v);
}


/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
struct DXMat4Tests : public Test
{
    XMMATRIX    a,b,c;
    Mat4        i,j,k;
    float       s;

    virtual void SetUp()
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
};
TEST_F(DXMat4Tests, Mat4Identity)
{
    a = XMMatrixIdentity();
    i = mat4_identity;
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Scale)
{
    float x = _rand_float(0.1f, 25.0f),
          y = _rand_float(0.1f, 25.0f),
          z = _rand_float(0.1f, 25.0f);
    a = XMMatrixScaling(x,y,z);
    i = mat4_scalef(x,y,z);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4RotateX)
{
    a = XMMatrixRotationX(s);
    i = mat4_rotation_x(s);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4RotateY)
{
    a = XMMatrixRotationY(s);
    i = mat4_rotation_y(s);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4RotateZ)
{
    a = XMMatrixRotationZ(s);
    i = mat4_rotation_z(s);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Rotate)
{
    float x = _rand_float(0.1f, 25.0f),
          y = _rand_float(0.1f, 25.0f),
          z = _rand_float(0.1f, 25.0f);
    a = XMMatrixRotationAxis(XMVectorSet(x,y,z,0.0f), s);
    i = mat4_rotation_axis(vec3_create(x,y,z), s);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Multiply)
{
    a = b*c;
    i = mat4_multiply(j,k);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Determinant)
{
    EXPECT_NEAR(XMVectorGetX(XMMatrixDeterminant(a)), mat4_determinant(i), 0.5);
}
TEST_F(DXMat4Tests, Mat4Transpose)
{
    a = XMMatrixTranspose(a);
    i = mat4_transpose(i);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Inverse)
{
    a = XMMatrixInverse(NULL, a);
    i = mat4_inverse(i);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4MultiplyScalar)
{
    a = a * s;
    i = mat4_mul_scalar(i, s);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4MultiplyVector)
{
    float x = _rand_float(-25.0f, 25.0f),
          y = _rand_float(-25.0f, 25.0f),
          z = _rand_float(-25.0f, 25.0f),
          w = _rand_float(-25.0f, 25.0f);
    XMVECTOR u = XMVectorSet(x,y,z,w);
    Vec4 v = vec4_create(x,y,z,w);

    u = XMVector4Transform(u, a);
    v = mat4_mul_vector(v, i);
    EXPECT_VEC4_EQ((float*)&u, (float*)&v);
}

TEST_F(DXMat4Tests, Mat4Perspective)
{
    a = XMMatrixPerspectiveLH(1280, 720, 1.0f, 1000.0f);
    i = mat4_perspective(1280, 720, 1.0f, 1000.0f);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4PerspectiveFov)
{
    a = XMMatrixPerspectiveFovLH(1/3.0f, 1280.0f/720, 1.0f, 1000.0f);
    i = mat4_perspective_fov(1/3.0f, 1280.0f/720, 1.0f, 1000.0f);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4Ortho)
{
    a = XMMatrixOrthographicLH(1280, 720, 1.0f, 1000.0f);
    i = mat4_ortho(1280, 720, 1.0f, 1000.0f);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXMat4Tests, Mat4OrthoOffCenter)
{
    a = XMMatrixOrthographicOffCenterLH(-500, 500, -500, 500, -1.0f, 1.0f);
    i = mat4_ortho_off_center(-500, 500, -500, 500, -1.0f, 1.0f);
    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}

/******************************************************************************\
 * Quaternion                                                                  *
\******************************************************************************/
struct DXQuaternionTests : public Test
{
    XMVECTOR    a,b,c;
    Quaternion  i,j,k;
    float       s;

    virtual void SetUp()
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
};
TEST_F(DXQuaternionTests, CreateAxisAngle)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = XMQuaternionRotationAxis(XMVectorSet(x,y,z,0), s);
    i = quat_from_axis_anglef(x,y,z,s);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXQuaternionTests, DISABLED_CreateEuler)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f);
    a = XMQuaternionRotationRollPitchYaw(x,y,z);
    a = XMQuaternionNormalize(a);
    i = quat_from_euler(x,y,z);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
    // TODO: Change the order in `quat_from_euler`
}
TEST_F(DXQuaternionTests, Normalize)
{
    a = XMQuaternionNormalize(a);
    i = quat_normalize(i);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXQuaternionTests, ConvertToMatrix)
{
    a = XMQuaternionNormalize(a);
    XMMATRIX x = XMMatrixRotationQuaternion(a);
    Mat3 y = quat_to_mat3(i);
    EXPECT_MAT3_EQ((float*)&x, (float*)&y);
}
TEST_F(DXQuaternionTests, Conjugate)
{
    a = XMQuaternionConjugate(a);
    i = quat_conjugate(i);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXQuaternionTests, Inverse)
{
    a = XMQuaternionNormalize(a);
    a = XMQuaternionInverse(a);
    i = quat_inverse(i);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}
TEST_F(DXQuaternionTests, Multiply)
{
    a = XMQuaternionMultiply(b,c);
    i = quat_multiply(j, k);
    EXPECT_VEC4_EQ((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Transform                                                                  *
\******************************************************************************/
TEST(DXTransformTest, TransformToMatrix)
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

    EXPECT_MAT4_EQ((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Plane                                                                      *
\******************************************************************************/
TEST(DXPlaneTest, ConstructPlaneFromPoints)
{
    DirectX::XMVECTOR    a,b,c;
    Vec3        i,j,k;
    float x,y,z;

    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,0);
    i = vec3_create(x,y,z);
    
    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    b = DirectX::XMVectorSet(x,y,z,0);
    j = vec3_create(x,y,z);
    
    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    c = DirectX::XMVectorSet(x,y,z,0);
    k = vec3_create(x,y,z);

    XMVECTOR p1 = XMPlaneFromPoints(a,b,c);
    Plane p2 = plane_from_points(i,j,k);
    EXPECT_VEC4_EQ((float*)&p1, (float*)&p2);
}
TEST(DXPlaneTest, ConstructPlaneFromPointNormal)
{
    DirectX::XMVECTOR    a,an;
    Vec3        i,in;
    float x,y,z;

    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,0);
    i = vec3_create(x,y,z);
    
    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    an = DirectX::XMVectorSet(x,y,z,0);
    in = vec3_create(x,y,z);

    an = DirectX::XMVector3Normalize(an);
    in = vec3_normalize(in);

    XMVECTOR p1 = XMPlaneFromPointNormal(a, an);
    Plane p2 = plane_from_point_normal(i, in);
    EXPECT_VEC4_EQ((float*)&p1, (float*)&p2);
}
TEST(DXPlaneTest, PointDistanceFromPlane)
{
    DirectX::XMVECTOR    a,an;
    Vec3        i,in;
    float x,y,z;

    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    a = DirectX::XMVectorSet(x,y,z,0);
    i = vec3_create(x,y,z);
    
    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    an = DirectX::XMVectorSet(x,y,z,0);
    in = vec3_create(x,y,z);

    an = DirectX::XMVector3Normalize(an);
    in = vec3_normalize(in);

    XMVECTOR p1 = XMPlaneFromPointNormal(a, an);
    Plane p2 = plane_from_point_normal(i, in);
    
    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    DirectX::XMVECTOR pt1 = DirectX::XMVectorSet(x,y,z,0);
    Vec3 pt2 = vec3_create(x,y,z);

    EXPECT_FLOAT_EQ(XMVectorGetX(XMPlaneDotCoord(p1, pt1)), plane_distance_point(p2, pt2));
}
TEST(DXPlaneTest, NormalizePlane)
{
    float x,y,z,w;

    x = _rand_float(-500.0f, 500.0f),
    y = _rand_float(-500.0f, 500.0f),
    z = _rand_float(-500.0f, 500.0f);
    w = _rand_float(-500.0f, 500.0f);

    XMVECTOR p1 = XMVectorSet(x,y,z,w);
    Plane p2 = {x,y,z,w};
    EXPECT_VEC4_EQ((float*)&p1, (float*)&p2);

    p1 = XMPlaneNormalize(p1);
    p2 = plane_normalize(p2);
    EXPECT_VEC4_EQ((float*)&p1, (float*)&p2);
}


} // Anonymous namespace
