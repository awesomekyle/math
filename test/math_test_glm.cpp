/** @file math_test_glm.cpp
 *  @copyright Copyright (c) 2014 Kyle Weicht. All rights reserved.
 */

#ifdef _MSC_VER
    #pragma warning(disable:4201) /* nameless struct */
    #pragma warning(disable:4505) /* Unreferenced function */
#endif

#include "vec_math.h"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define CHECK_EQUAL_VEC2(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f)

#define CHECK_EQUAL_VEC3(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f); \
    EXPECT_NEAR((a)[2], (b)[2], 0.001f)

#define CHECK_EQUAL_VEC4(a,b) \
    EXPECT_NEAR((a)[0], (b)[0], 0.001f); \
    EXPECT_NEAR((a)[1], (b)[1], 0.001f); \
    EXPECT_NEAR((a)[2], (b)[2], 0.001f); \
    EXPECT_NEAR((a)[3], (b)[3], 0.001f)

#define CHECK_EQUAL_MAT3(expected, actual)  \
    for(int ii=0;ii<9;++ii) {                   \
        EXPECT_NEAR((expected)[ii], (actual)[ii], 0.001f);    \
    }

#define CHECK_EQUAL_MAT4(expected, actual)  \
    for(int ii=0;ii<16;++ii) {                   \
        EXPECT_NEAR((expected)[ii], (actual)[ii], 0.001f);    \
    }

namespace GLMTests
{

template<typename T>
inline T glm_lerp(const T& a, const T& b, float t)
{
    return a + (b-a)*t;
}

float _rand_float(float min, float max)
{
    float f = rand()/(float)RAND_MAX;
    f *= (max-min);
    return f+min;
}

/******************************************************************************\
 * Vec2                                                                       *
\******************************************************************************/
struct GLMVec2Fixture : public Test
{
    glm::vec2   a,b,c;
    Vec2        i,j,k;
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
TEST_F(GLMVec2Fixture, Vec2Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f);
    a = glm::vec2(x,y);
    i = vec2_create(x,y);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}

TEST_F(GLMVec2Fixture, Vec2Zero)
{
    a = glm::vec2(0.0f);
    i = vec2_zero;
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Add)
{
    a = b+c;
    i = vec2_add(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Sub)
{
    a = b-c;
    i = vec2_sub(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Mul)
{
    a = b*c;
    i = vec2_mul(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Div)
{
    a = b/c;
    i = vec2_div(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}

TEST_F(GLMVec2Fixture, Vec2AddScalar)
{
    a = b+s;
    i = vec2_add_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2SubScalar)
{
    a = b-s;
    i = vec2_sub_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2MulScalar)
{
    a = b*s;
    i = vec2_mul_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2DivScalar)
{
    a = b/s;
    i = vec2_div_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Hadd)
{
    float expected = a.x+a.y;
    float actual = vec2_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(GLMVec2Fixture, Vec2Equal)
{
    EXPECT_TRUE(0 != vec2_equal(j, j));
    EXPECT_FALSE(vec2_equal(j, k));
}
TEST_F(GLMVec2Fixture, Vec2Length)
{
    EXPECT_FLOAT_EQ(glm::length(a), vec2_length(i));
}
TEST_F(GLMVec2Fixture, Vec2Distance)
{
    EXPECT_FLOAT_EQ(glm::distance(a,b), vec2_distance(i,j));
    EXPECT_FLOAT_EQ(vec2_distance(j,i), vec2_distance(i,j));
}
TEST_F(GLMVec2Fixture, Vec2Normalize)
{
    a = glm::normalize(a);
    i = vec2_normalize(i);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2MinMax)
{
    a = glm::max(b, c);
    i = vec2_max(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec2_min(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
    i = vec2_lerp(j,k,f);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_F(GLMVec2Fixture, Vec2Negate)
{
    a = -b;
    i = vec2_negate(j);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Vec3                                                                       *
\******************************************************************************/
struct GLMVec3Fixture : public Test
{
    glm::vec3   a,b,c;
    Vec3        i,j,k;
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
TEST_F(GLMVec3Fixture, Vec4FromVec3)
{
    glm::vec4 x = glm::vec4(a,1.0f);
    Vec4 y = vec4_from_vec3(i,1.0f);
    CHECK_EQUAL_VEC4((float*)&x, (float*)&y);
}
TEST_F(GLMVec3Fixture, Vec3Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f);
    a = glm::vec3(x,y,z);
    i = vec3_create(x,y,z);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Zero)
{
    a = glm::vec3(0.0f);
    i = vec3_zero;
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Add)
{
    a = b+c;
    i = vec3_add(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Sub)
{
    a = b-c;
    i = vec3_sub(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Mul)
{
    a = b*c;
    i = vec3_mul(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Div)
{
    a = b/c;
    i = vec3_div(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}

TEST_F(GLMVec3Fixture, Vec3AddScalar)
{
    a = b+s;
    i = vec3_add_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3SubScalar)
{
    a = b-s;
    i = vec3_sub_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3MulScalar)
{
    a = b*s;
    i = vec3_mul_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3DivScalar)
{
    a = b/s;
    i = vec3_div_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Hadd)
{
    float expected = a.x+a.y+a.z;
    float actual = vec3_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(GLMVec3Fixture, Vec3Equal)
{
    EXPECT_TRUE(0 != vec3_equal(j, j));
    EXPECT_FALSE(vec3_equal(j, k));
}
TEST_F(GLMVec3Fixture, Vec3Length)
{
    EXPECT_FLOAT_EQ(glm::length(a), vec3_length(i));
}
TEST_F(GLMVec3Fixture, Vec3Distance)
{
    EXPECT_FLOAT_EQ(glm::distance(a,b), vec3_distance(i,j));
    EXPECT_FLOAT_EQ(vec3_distance(j,i), vec3_distance(i,j));
}
TEST_F(GLMVec3Fixture, Vec3Normalize)
{
    a = glm::normalize(a);
    i = vec3_normalize(i);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3MinMax)
{
    a = glm::max(b, c);
    i = vec3_max(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec3_min(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
    i = vec3_lerp(j,k,f);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Negate)
{
    a = -b;
    i = vec3_negate(j);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_F(GLMVec3Fixture, Vec3Dot)
{
    EXPECT_FLOAT_EQ(glm::dot(a,b), vec3_dot(i,j));
}
TEST_F(GLMVec3Fixture, Vec3Cross)
{
    a = glm::cross(b,c);
    i = vec3_cross(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Vec4                                                                       *
\******************************************************************************/
struct GLMVec4Fixture : public Test
{
    glm::vec4   a,b,c;
    Vec4        i,j,k;
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
TEST_F(GLMVec4Fixture, Vec3FromVec4)
{
    glm::vec3 x = glm::vec3(a);
    Vec3 y = vec3_from_vec4(i);
    CHECK_EQUAL_VEC3((float*)&x, (float*)&y);
}
TEST_F(GLMVec4Fixture, Vec4Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f),
          w = _rand_float(-500.0f, 500.0f);
    a = glm::vec4(x,y,z,w);
    i = vec4_create(x,y,z,w);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Zero)
{
    a = glm::vec4(0.0f);
    i = vec4_zero;
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Add)
{
    a = b+c;
    i = vec4_add(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Sub)
{
    a = b-c;
    i = vec4_sub(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Mul)
{
    a = b*c;
    i = vec4_mul(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Div)
{
    a = b/c;
    i = vec4_div(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}

TEST_F(GLMVec4Fixture, Vec4AddScalar)
{
    a = b+s;
    i = vec4_add_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4SubScalar)
{
    a = b-s;
    i = vec4_sub_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4MulScalar)
{
    a = b*s;
    i = vec4_mul_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4DivScalar)
{
    a = b/s;
    i = vec4_div_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Hadd)
{
    float expected = a.x+a.y+a.z+a.w;
    float actual = vec4_hadd(i);
    EXPECT_FLOAT_EQ(expected, actual);
}
TEST_F(GLMVec4Fixture, Vec4Equal)
{
    EXPECT_TRUE(0 != vec4_equal(j, j));
    EXPECT_FALSE(vec4_equal(j, k));
}
TEST_F(GLMVec4Fixture, Vec4Length)
{
    EXPECT_FLOAT_EQ(glm::length(a), vec4_length(i));
}
TEST_F(GLMVec4Fixture, Vec4Distance)
{
    EXPECT_FLOAT_EQ(glm::distance(a,b), vec4_distance(i,j));
    EXPECT_FLOAT_EQ(vec4_distance(j,i), vec4_distance(i,j));
}
TEST_F(GLMVec4Fixture, Vec4Normalize)
{
    a = glm::normalize(a);
    i = vec4_normalize(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4MinMax)
{
    a = glm::max(b, c);
    i = vec4_max(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec4_min(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
    i = vec4_lerp(j,k,f);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMVec4Fixture, Vec4Negate)
{
    a = -b;
    i = vec4_negate(j);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}

/******************************************************************************\
 * Mat3                                                                       *
\******************************************************************************/
struct GLMMat3Fixture : public Test
{
    glm::mat3   a,b,c;
    Mat3        i,j,k;
    float       s;

    virtual void SetUp()
    {
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a + sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-50.0f, 50.0f);
    }
};
TEST_F (GLMMat3Fixture, Mat4FromMat3)
{
    glm::mat4 x = glm::mat4(a);
    Mat4 y = mat4_from_mat3(i);
    CHECK_EQUAL_MAT4((float*)&x, (float*)&y);
}
TEST_F(GLMMat3Fixture, Mat3Identity)
{
    a = glm::mat3();
    i = mat3_identity;
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3Scale)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat3)glm::scale(glm::mat4(), glm::vec3(x,y,z));
    i = mat3_scalef(x,y,z);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3RotateX)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(1,0,0));
    i = mat3_rotation_x(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3RotateY)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(0,1,0));
    i = mat3_rotation_y(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3RotateZ)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(0,0,1));
    i = mat3_rotation_z(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3Rotate)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(x,y,z));
    i = mat3_rotation_axis(vec3_create(x,y,z), s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3Multiply)
{
    a = c*b; // NOTE: These are reversed because the library is column major, not row
    i = mat3_multiply(j,k);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3Determinant)
{
    EXPECT_NEAR(glm::determinant(a), mat3_determinant(i), 0.5);
}
TEST_F(GLMMat3Fixture, Mat3Transpose)
{
    a = glm::transpose(a);
    i = mat3_transpose(i);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3Inverse)
{
    a = glm::inverse(a);
    i = mat3_inverse(i);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3MultiplyScalar)
{
    a = a * s;
    i = mat3_mul_scalar(i, s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_F(GLMMat3Fixture, Mat3MultiplyVector)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f);
    glm::vec3 u(x,y,z);
    Vec3 v = vec3_create(x,y,z);

    u = a * u;
    v = mat3_mul_vector(v, i);
    CHECK_EQUAL_VEC3((float*)&u, (float*)&v);
}

/******************************************************************************\
 * Mat4                                                                       *
\******************************************************************************/
struct GLMMat4Fixture : public Test
{
    glm::mat4   a,b,c;
    Mat4        i,j,k;
    float       s;

    virtual void SetUp()
    {
        float* _a = (float*)&a;
        float* _b = (float*)&i;
        float* end = _a + sizeof(a)/sizeof(float) * 3;
        while(_a != end) {
            *_b = *_a = _rand_float(-50.0f, 50.0f);
            ++_a, ++_b;
        }
        s = _rand_float(-50.0f, 50.0f);
    }
};
TEST_F (GLMMat4Fixture, Mat3FromMat4)
{
    glm::mat3 x = glm::mat3(a);
    Mat3 y = mat3_from_mat4(i);
    CHECK_EQUAL_MAT3((float*)&x, (float*)&y);
}
TEST_F(GLMMat4Fixture, Mat4Identity)
{
    a = glm::mat4();
    i = mat4_identity;
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Scale)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat4)glm::scale(glm::mat4(), glm::vec3(x,y,z));
    i = mat4_scalef(x,y,z);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Translate)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f);
    a = (glm::mat4)glm::translate(glm::mat4(), glm::vec3(x,y,z));
    i = mat4_translatef(x,y,z);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4RotateX)
{
    a = (glm::mat4)glm::rotate(glm::mat4(), s, glm::vec3(1,0,0));
    i = mat4_rotation_x(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4RotateY)
{
    a = (glm::mat4)glm::rotate(glm::mat4(), s, glm::vec3(0,1,0));
    i = mat4_rotation_y(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4RotateZ)
{
    a = (glm::mat4)glm::rotate(glm::mat4(), s, glm::vec3(0,0,1));
    i = mat4_rotation_z(s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Rotate)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat4)glm::rotate(glm::mat4(), s, glm::vec3(x,y,z));
    i = mat4_rotation_axis(vec3_create(x,y,z), s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Multiply)
{
    a = c*b; // NOTE: These are reversed because the library is column major, not row
    i = mat4_multiply(j,k);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Determinant)
{
    EXPECT_NEAR(glm::determinant(a), mat4_determinant(i), 0.5);
}
TEST_F(GLMMat4Fixture, Mat4Transpose)
{
    a = glm::transpose(a);
    i = mat4_transpose(i);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4Inverse)
{
    a = glm::inverse(a);
    i = mat4_inverse(i);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4MultiplyScalar)
{
    a = a * s;
    i = mat4_mul_scalar(i, s);
    CHECK_EQUAL_MAT4((float*)&a, (float*)&i);
}
TEST_F(GLMMat4Fixture, Mat4MultiplyVector)
{
    float x = _rand_float(-50.0f, 50.0f),
          y = _rand_float(-50.0f, 50.0f),
          z = _rand_float(-50.0f, 50.0f),
          w = _rand_float(-50.0f, 50.0f);
    glm::vec4 u(x,y,z,w);
    Vec4 v = vec4_create(x,y,z,w);

    u = a * u;
    v = mat4_mul_vector(v, i);
    CHECK_EQUAL_VEC4((float*)&u, (float*)&v);
}

/******************************************************************************\
 * Quaternion                                                                  *
\******************************************************************************/
struct GLMQuaternionFixture : public Test
{
    glm::quat   a,b,c;
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
TEST_F(GLMQuaternionFixture, Create)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = glm::angleAxis(s,glm::normalize(glm::vec3(x,y,z)));
    i = quat_from_axis_anglef(x,y,z,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMQuaternionFixture, Normalize)
{
    a = glm::normalize(a);
    i = quat_normalize(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMQuaternionFixture, ConvertToMatrix)
{
    a = glm::normalize(a);
    glm::mat3 x = glm::mat3_cast(a);
    Mat3 y = quat_to_mat3(i);
    CHECK_EQUAL_MAT3((float*)&x, (float*)&y);
}
TEST_F(GLMQuaternionFixture, Conjugate)
{
    a = glm::conjugate(a);
    i = quat_conjugate(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMQuaternionFixture, Inverse)
{
    a = glm::normalize(a);
    a = glm::inverse(a);
    i = quat_inverse(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_F(GLMQuaternionFixture, Multiply)
{
    a = c * b;
    i = quat_multiply(j, k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}

} // anonymous namespace
