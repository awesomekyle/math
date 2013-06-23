/** @file math_test.cpp
 *  @copyright Copyright (c) 2013 Kyle Weicht. All rights reserved.
 */
#include "unit_test.h"

#include "vec_math.h"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    for(int ii=0;ii<9;++ii) {                   \
        CHECK_EQUAL_FLOAT((expected)[ii], (actual)[ii]);    \
    }

namespace
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
    return f-min;
}

/******************************************************************************\
 * Vec2                                                                       *
\******************************************************************************/
struct Vec2Fixture
{
    glm::vec2   a,b,c;
    Vec2        i,j,k;
    float       s;

    Vec2Fixture()
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
    ~Vec2Fixture() { }
};
TEST_FIXTURE(Vec2Fixture, Vec2Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f);
    a = glm::vec2(x,y);
    i = vec2_create(x,y);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Zero)
{
    a = glm::vec2(0.0f);
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
    a = b+s;
    i = vec2_add_scalar(j,s);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2SubScalar)
{
    a = b-s;
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
    float expected = a.x+a.y;
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
    CHECK_EQUAL_FLOAT(glm::length(a), vec2_length(i));
}
TEST_FIXTURE(Vec2Fixture, Vec2Distance)
{
    CHECK_EQUAL_FLOAT(glm::distance(a,b), vec2_distance(i,j));
    CHECK_EQUAL_FLOAT(vec2_distance(j,i), vec2_distance(i,j));
}
TEST_FIXTURE(Vec2Fixture, Vec2Normalize)
{
    a = glm::normalize(a);
    i = vec2_normalize(i);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2MinMax)
{
    a = glm::max(b, c);
    i = vec2_max(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec2_min(j,k);
    CHECK_EQUAL_VEC2((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec2Fixture, Vec2Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
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
    glm::vec3   a,b,c;
    Vec3        i,j,k;
    float       s;

    Vec3Fixture()
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
    ~Vec3Fixture() { }
};
TEST_FIXTURE(Vec3Fixture, Vec3Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f);
    a = glm::vec3(x,y,z);
    i = vec3_create(x,y,z);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Zero)
{
    a = glm::vec3(0.0f);
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
    a = b+s;
    i = vec3_add_scalar(j,s);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3SubScalar)
{
    a = b-s;
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
    float expected = a.x+a.y+a.z;
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
    CHECK_EQUAL_FLOAT(glm::length(a), vec3_length(i));
}
TEST_FIXTURE(Vec3Fixture, Vec3Distance)
{
    CHECK_EQUAL_FLOAT(glm::distance(a,b), vec3_distance(i,j));
    CHECK_EQUAL_FLOAT(vec3_distance(j,i), vec3_distance(i,j));
}
TEST_FIXTURE(Vec3Fixture, Vec3Normalize)
{
    a = glm::normalize(a);
    i = vec3_normalize(i);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3MinMax)
{
    a = glm::max(b, c);
    i = vec3_max(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec3_min(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec3Fixture, Vec3Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
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
    CHECK_EQUAL_FLOAT(glm::dot(a,b), vec3_dot(i,j));
}
TEST_FIXTURE(Vec3Fixture, Vec3Cross)
{
    a = glm::cross(b,c);
    i = vec3_cross(j,k);
    CHECK_EQUAL_VEC3((float*)&a, (float*)&i);
}


/******************************************************************************\
 * Vec4                                                                       *
\******************************************************************************/
struct Vec4Fixture
{
    glm::vec4   a,b,c;
    Vec4        i,j,k;
    float       s;

    Vec4Fixture()
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
    ~Vec4Fixture() { }
};
TEST_FIXTURE(Vec4Fixture, Vec4Creation)
{
    float x = _rand_float(-500.0f, 500.0f),
          y = _rand_float(-500.0f, 500.0f),
          z = _rand_float(-500.0f, 500.0f),
          w = _rand_float(-500.0f, 500.0f);
    a = glm::vec4(x,y,z,w);
    i = vec4_create(x,y,z,w);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Zero)
{
    a = glm::vec4(0.0f);
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
    a = b+s;
    i = vec4_add_scalar(j,s);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4SubScalar)
{
    a = b-s;
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
    float expected = a.x+a.y+a.z+a.w;
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
    CHECK_EQUAL_FLOAT(glm::length(a), vec4_length(i));
}
TEST_FIXTURE(Vec4Fixture, Vec4Distance)
{
    CHECK_EQUAL_FLOAT(glm::distance(a,b), vec4_distance(i,j));
    CHECK_EQUAL_FLOAT(vec4_distance(j,i), vec4_distance(i,j));
}
TEST_FIXTURE(Vec4Fixture, Vec4Normalize)
{
    a = glm::normalize(a);
    i = vec4_normalize(i);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4MinMax)
{
    a = glm::max(b, c);
    i = vec4_max(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
    a = glm::min(b, c);
    i = vec4_min(j,k);
    CHECK_EQUAL_VEC4((float*)&a, (float*)&i);
}
TEST_FIXTURE(Vec4Fixture, Vec4Lerp)
{
    float f = _rand_float(0.0f, 1.0f);
    a = glm_lerp(b,c,f);
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
    glm::mat3   a,b,c;
    Mat3        i,j,k;
    float       s;

    Mat3Fixture()
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
    ~Mat3Fixture() { }
};
TEST_FIXTURE(Mat3Fixture, Mat3Identity)
{
    a = glm::mat3();
    i = mat3_identity;
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Scale)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat3)glm::scale(glm::mat4(), glm::vec3(x,y,z));
    i = mat3_scalef(x,y,z);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateX)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(1,0,0));
    i = mat3_rotation_x(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateY)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(0,1,0));
    i = mat3_rotation_y(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3RotateZ)
{
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(0,0,1));
    i = mat3_rotation_z(s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Rotate)
{
    float x = _rand_float(0.1f, 50.0f),
          y = _rand_float(0.1f, 50.0f),
          z = _rand_float(0.1f, 50.0f);
    a = (glm::mat3)glm::rotate(glm::mat4(), s, glm::vec3(x,y,z));
    i = mat3_rotation_axis(vec3_create(x,y,z), s);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Multiply)
{
    a = c*b; // NOTE: These are reversed because the library is column major, not row
    i = mat3_multiply(j,k);
    CHECK_EQUAL_MAT3((float*)&a, (float*)&i);
}
TEST_FIXTURE(Mat3Fixture, Mat3Determinant)
{
    CHECK_EQUAL_FLOAT_EPSILON(glm::determinant(a), mat3_determinant(i), 0.5);
}

} // anonymous namespace
