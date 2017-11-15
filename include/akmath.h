#pragma once
#include <math.h>

namespace ak {

struct Vec2
{
    float x;
    float y;
};
struct Vec3
{
    float x;
    float y;
    float z;
};
struct Vec4
{
    float x;
    float y;
    float z;
    float w;
};

struct Mat3
{
    Vec3 c0;
    Vec3 c1;
    Vec3 c2;

    inline static Mat3 Identity();
    inline static Mat3 Scaling(float const x, float const y, float const z);
    inline static Mat3 RotationX(float const rad);
    inline static Mat3 RotationY(float const rad);
    inline static Mat3 RotationZ(float const rad);
    inline static Mat3 RotationAxis(Vec3 const axis, float const rad);
};

/*****************************************************************************\
 * Vec2                                                                       *
\*****************************************************************************/
constexpr inline Vec2 operator+(Vec2 const a, Vec2 const b)
{
    return {a.x + b.x, a.y + b.y};
}
constexpr inline Vec2 operator-(Vec2 const a, Vec2 const b)
{
    return {a.x - b.x, a.y - b.y};
}
constexpr inline Vec2 operator*(Vec2 const a, Vec2 const b)
{
    return {a.x * b.x, a.y * b.y};
}
constexpr inline Vec2 operator/(Vec2 const a, Vec2 const b)
{
    return {a.x / b.x, a.y / b.y};
}

constexpr inline Vec2 operator*(Vec2 const a, float const f)
{
    return {a.x * f, a.y * f};
}
constexpr inline Vec2 operator/(Vec2 const a, float const f)
{
    return {a.x / f, a.y / f};
}

// Vec2 misc
inline float LengthSq(Vec2 const a)
{
    return a.x * a.x + a.y * a.y;
}
inline float Length(Vec2 const a)
{
    return sqrtf(LengthSq(a));
}
inline float DistanceSq(Vec2 const a, Vec2 const b)
{
    return LengthSq(a - b);
}
inline float Distance(Vec2 const a, Vec2 const b)
{
    return sqrtf(DistanceSq(a, b));
}
inline Vec2 Normalize(Vec2 const v)
{
    float const length = Length(v);
    return v / length;
}
inline Vec2 Min(Vec2 const a, Vec2 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y};
}
inline Vec2 Max(Vec2 const a, Vec2 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y};
}
inline Vec2 Lerp(Vec2 const a, Vec2 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

inline Vec2 operator-(Vec2 const v)
{
    return {-v.x, -v.y};
}

/*****************************************************************************\
 * Vec3                                                                       *
\*****************************************************************************/
constexpr inline Vec3 operator+(Vec3 const a, Vec3 const b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
constexpr inline Vec3 operator-(Vec3 const a, Vec3 const b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
constexpr inline Vec3 operator*(Vec3 const a, Vec3 const b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z};
}
constexpr inline Vec3 operator/(Vec3 const a, Vec3 const b)
{
    return {a.x / b.x, a.y / b.y, a.z / b.z};
}

constexpr inline Vec3 operator*(Vec3 const a, float const f)
{
    return {a.x * f, a.y * f, a.z * f};
}
constexpr inline Vec3 operator/(Vec3 const a, float const f)
{
    return {a.x / f, a.y / f, a.z / f};
}

// Vec3 misc
inline float LengthSq(Vec3 const a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}
inline float Length(Vec3 const a)
{
    return sqrtf(LengthSq(a));
}
inline float DistanceSq(Vec3 const a, Vec3 const b)
{
    return LengthSq(a - b);
}
inline float Distance(Vec3 const a, Vec3 const b)
{
    return sqrtf(DistanceSq(a, b));
}
inline Vec3 Normalize(Vec3 const v)
{
    float const length = Length(v);
    return v / length;
}
inline Vec3 Min(Vec3 const a, Vec3 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z};
}
inline Vec3 Max(Vec3 const a, Vec3 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z};
}
inline Vec3 Lerp(Vec3 const a, Vec3 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

inline Vec3 operator-(Vec3 const v)
{
    return {-v.x, -v.y, -v.z};
}

inline float Dot(Vec3 const a, Vec3 const b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline Vec3 Cross(Vec3 const a, Vec3 const b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}

/*****************************************************************************\
 * Vec4                                                                       *
\*****************************************************************************/
constexpr inline Vec4 operator+(Vec4 const a, Vec4 const b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}
constexpr inline Vec4 operator-(Vec4 const a, Vec4 const b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}
constexpr inline Vec4 operator*(Vec4 const a, Vec4 const b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}
constexpr inline Vec4 operator/(Vec4 const a, Vec4 const b)
{
    return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
}

constexpr inline Vec4 operator*(Vec4 const a, float const f)
{
    return {a.x * f, a.y * f, a.z * f, a.w * f};
}
constexpr inline Vec4 operator/(Vec4 const a, float const f)
{
    return {a.x / f, a.y / f, a.z / f, a.w / f};
}

// Vec4 misc
inline float LengthSq(Vec4 const a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}
inline float Length(Vec4 const a)
{
    return sqrtf(LengthSq(a));
}
inline float DistanceSq(Vec4 const a, Vec4 const b)
{
    return LengthSq(a - b);
}
inline float Distance(Vec4 const a, Vec4 const b)
{
    return sqrtf(DistanceSq(a, b));
}
inline Vec4 Normalize(Vec4 const v)
{
    float const length = Length(v);
    return v / length;
}
inline Vec4 Min(Vec4 const a, Vec4 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z,
            a.w < b.w ? a.w : b.w};
}
inline Vec4 Max(Vec4 const a, Vec4 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z,
            a.w > b.w ? a.w : b.w};
}
inline Vec4 Lerp(Vec4 const a, Vec4 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

inline Vec4 operator-(Vec4 const v)
{
    return {-v.x, -v.y, -v.z, -v.w};
}

/*****************************************************************************\
 * Mat3                                                                       *
\*****************************************************************************/
inline Mat3 Mat3::Identity()
{
    return {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
}
inline Mat3 Mat3::Scaling(float const x, float const y, float const z)
{
    return {
        {x, 0, 0},
        {0, y, 0},
        {0, 0, z},
    };
}
inline Mat3 Mat3::RotationX(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {1, 0, 0},
        {0, c, -s},
        {0, s, c},
    };
}
inline Mat3 Mat3::RotationY(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, 0, s},
        {0, 1, 0},
        {-s, 0, c},
    };
}
inline Mat3 Mat3::RotationZ(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, -s, 0},
        {s, c, 0},
        {0, 0, 1},
    };
}
inline Mat3 Mat3::RotationAxis(Vec3 const axis, float const rad)
{
    Vec3 const normAxis = Normalize(axis);
    float const c = cosf(rad);
    float const s = sinf(rad);
    float const t = 1.0f - c;

    float const x = normAxis.x;
    float const y = normAxis.y;
    float const z = normAxis.z;

    return {
        {(t * x * x) + c, (t * x * y) - (s * z), (t * x * z) + (s * y)},
        {(t * x * y) + s * z, (t * y * y) + c, (t * y * z) - (s * x)},
        {(t * x * z) - s * y, (t * y * z) + (s * x), (t * z * z) + c},
    };
}
inline Mat3 operator*(Mat3 const a, Mat3 const b)
{
#define MTX3_INDEX(f, r, c) ((f)[(r * 3) + c])

    Mat3 m{};

    const float* left = &a.c0.x;
    const float* right = &b.c0.x;
    float* result = (float*)&m;

    for (int ii = 0; ii < 3; ++ii) /* row */
    {
        for (int jj = 0; jj < 3; ++jj) /* column */
        {
            float sum = MTX3_INDEX(left, ii, 0) * MTX3_INDEX(right, 0, jj);
            for (int kk = 1; kk < 3; ++kk) {
                sum += (MTX3_INDEX(left, ii, kk) * MTX3_INDEX(right, kk, jj));
            }
            MTX3_INDEX(result, ii, jj) = sum;
        }
    }
    return m;
#undef MTX3_INDEX
}

}  // namespace ak
