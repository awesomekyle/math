#pragma once
#include <math.h>
#include <immintrin.h>
#include <cstdalign>

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
struct alignas(16) Vec4
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

    constexpr inline static Mat3 Identity();
    constexpr inline static Mat3 Scaling(float const x, float const y, float const z);
    inline static Mat3 RotationX(float const rad);
    inline static Mat3 RotationY(float const rad);
    inline static Mat3 RotationZ(float const rad);
    inline static Mat3 RotationAxis(Vec3 const axis, float const rad);
};

struct alignas(64) Mat4
{
    Vec4 c0;
    Vec4 c1;
    Vec4 c2;
    Vec4 c3;

    constexpr inline static Mat4 Identity();
    constexpr inline static Mat4 Scaling(float const x, float const y, float const z);
    inline static Mat4 RotationX(float const rad);
    inline static Mat4 RotationY(float const rad);
    inline static Mat4 RotationZ(float const rad);
    inline static Mat4 RotationAxis(Vec4 const axis, float const rad);
};

inline void _swapf(float& a, float& b)
{
    float const t = a;
    a = b;
    b = t;
}

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
constexpr inline float LengthSq(Vec2 const a)
{
    return a.x * a.x + a.y * a.y;
}
inline float Length(Vec2 const a)
{
    return sqrtf(LengthSq(a));
}
constexpr inline float DistanceSq(Vec2 const a, Vec2 const b)
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
constexpr inline Vec2 Min(Vec2 const a, Vec2 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y};
}
constexpr inline Vec2 Max(Vec2 const a, Vec2 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y};
}
constexpr inline Vec2 Lerp(Vec2 const a, Vec2 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

constexpr inline Vec2 operator-(Vec2 const v)
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
constexpr inline float LengthSq(Vec3 const a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}
inline float Length(Vec3 const a)
{
    return sqrtf(LengthSq(a));
}
constexpr inline float DistanceSq(Vec3 const a, Vec3 const b)
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
constexpr inline Vec3 Min(Vec3 const a, Vec3 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z};
}
constexpr inline Vec3 Max(Vec3 const a, Vec3 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z};
}
constexpr inline Vec3 Lerp(Vec3 const a, Vec3 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

constexpr inline Vec3 operator-(Vec3 const v)
{
    return {-v.x, -v.y, -v.z};
}

constexpr inline float Dot(Vec3 const a, Vec3 const b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
constexpr inline Vec3 Cross(Vec3 const a, Vec3 const b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}
constexpr inline float Hadd(Vec3 const v)
{
    return v.x + v.y + v.z;
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
constexpr inline float LengthSq(Vec4 const a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}
inline float Length(Vec4 const a)
{
    return sqrtf(LengthSq(a));
}
constexpr inline float DistanceSq(Vec4 const a, Vec4 const b)
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
constexpr inline Vec4 Min(Vec4 const a, Vec4 const b)
{
    return {a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y, a.z < b.z ? a.z : b.z,
            a.w < b.w ? a.w : b.w};
}
constexpr inline Vec4 Max(Vec4 const a, Vec4 const b)
{
    return {a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y, a.z > b.z ? a.z : b.z,
            a.w > b.w ? a.w : b.w};
}
constexpr inline Vec4 Lerp(Vec4 const a, Vec4 const b, float const t)
{
    auto const d = b - a;
    return a + (d * t);
}

constexpr inline Vec4 operator-(Vec4 const v)
{
    return {-v.x, -v.y, -v.z, -v.w};
}

constexpr inline float Hadd(Vec4 const v)
{
    return v.x + v.y + v.z + v.w;
}

/*****************************************************************************\
 * Mat3                                                                       *
\*****************************************************************************/
constexpr inline Mat3 Mat3::Identity()
{
    return {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
}
constexpr inline Mat3 Mat3::Scaling(float const x, float const y, float const z)
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
        {0, c, s},
        {0, -s, c},
    };
}
inline Mat3 Mat3::RotationY(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, 0, -s},
        {0, 1, 0},
        {s, 0, c},
    };
}
inline Mat3 Mat3::RotationZ(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, s, 0},
        {-s, c, 0},
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
        {
            (t * x * x) + c,
            (t * x * y) + s * z,
            (t * x * z) - s * y,
        },
        {
            (t * x * y) - (s * z),
            (t * y * y) + c,
            (t * y * z) + (s * x),
        },
        {
            (t * x * z) + (s * y),
            (t * y * z) - (s * x),
            (t * z * z) + c,
        },
    };
}
constexpr inline Mat3 operator*(Mat3 const a, Mat3 const b)
{
    Mat3 m{};

    float const(*const left)[3] = (float(*)[3]) & a.c0.x;
    float const(*const right)[3] = (float(*)[3]) & b.c0.x;
    float(*result)[3] = (float(*)[3]) & m;

    for (int ii = 0; ii < 3; ++ii) /* column */
    {
        for (int jj = 0; jj < 3; ++jj) /* row */
        {
            for (int kk = 0; kk < 3; ++kk) {
                result[jj][ii] += (left[kk][ii] * right[jj][kk]);
            }
        }
    }
    return m;
}
inline void TransposeInPlace(Mat3& m)
{
    _swapf(m.c0.y, m.c1.x);
    _swapf(m.c0.z, m.c2.x);
    _swapf(m.c1.z, m.c2.y);
}
inline Mat3 Transpose(Mat3 m)
{
    TransposeInPlace(m);
    return m;
}

constexpr inline float Determinant(Mat3 const m)
{
    float const f0 = m.c0.x * (m.c1.y * m.c2.z - m.c2.y * m.c1.z);
    float const f1 = m.c0.y * -(m.c1.x * m.c2.z - m.c2.x * m.c1.z);
    float const f2 = m.c0.z * (m.c1.x * m.c2.y - m.c2.x * m.c1.y);
    return f0 + f1 + f2;
}

constexpr inline Mat3 operator*(Mat3 const m, float const f)
{
    return {m.c0 * f, m.c1 * f, m.c2 * f};
}
inline Mat3 Inverse(Mat3 m)
{
    float const det = Determinant(m);
    m = {
        {
            (m.c1.y * m.c2.z) - (m.c1.z * m.c2.y),
            -((m.c1.x * m.c2.z) - (m.c1.z * m.c2.x)),
            (m.c1.x * m.c2.y) - (m.c1.y * m.c2.x),
        },
        {
            -((m.c0.y * m.c2.z) - (m.c0.z * m.c2.y)),
            (m.c0.x * m.c2.z) - (m.c0.z * m.c2.x),
            -((m.c0.x * m.c2.y) - (m.c0.y * m.c2.x)),
        },
        {
            (m.c0.y * m.c1.z) - (m.c0.z * m.c1.y),
            -((m.c0.x * m.c1.z) - (m.c0.z * m.c1.x)),
            (m.c0.x * m.c1.y) - (m.c0.y * m.c1.x),
        },
    };

    TransposeInPlace(m);
    return m * (1.0f / det);
}

inline Vec3 operator*(Mat3 m, Vec3 const v)
{
    TransposeInPlace(m);
    return {
        Hadd(m.c0 * v),
        Hadd(m.c1 * v),
        Hadd(m.c2 * v),
    };
}

/*****************************************************************************\
 * Mat4                                                                       *
\*****************************************************************************/
constexpr inline Mat4 Mat4::Identity()
{
    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
}
constexpr inline Mat4 Mat4::Scaling(float const x, float const y, float const z)
{
    return {
        {x, 0, 0, 0},
        {0, y, 0, 0},
        {0, 0, z, 0},
        {0, 0, 0, 1},
    };
}
inline Mat4 Mat4::RotationX(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {1, 0, 0, 0},
        {0, c, s, 0},
        {0, -s, c, 0},
        {0, 0, 0, 1},
    };
}
inline Mat4 Mat4::RotationY(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, 0, -s, 0},
        {0, 1, 0, 0},
        {s, 0, c, 0},
        {0, 0, 0, 1},
    };
}
inline Mat4 Mat4::RotationZ(float const rad)
{
    float const c = cosf(rad);
    float const s = sinf(rad);
    return {
        {c, s, 0, 0},
        {-s, c, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
}
inline Mat4 Mat4::RotationAxis(Vec4 const axis, float const rad)
{
    Vec4 const normAxis = Normalize(axis);
    float const c = cosf(rad);
    float const s = sinf(rad);
    float const t = 1.0f - c;

    float const x = normAxis.x;
    float const y = normAxis.y;
    float const z = normAxis.z;

    return {
        {
            (t * x * x) + c,
            (t * x * y) + s * z,
            (t * x * z) - s * y,
            0,
        },
        {
            (t * x * y) - (s * z),
            (t * y * y) + c,
            (t * y * z) + (s * x),
            0,
        },
        {
            (t * x * z) + (s * y),
            (t * y * z) - (s * x),
            (t * z * z) + c,
            0,
        },
        {0, 0, 0, 1},
    };
}
constexpr inline Mat4 MultiplyScalar(Mat4 const a, Mat4 const b)
{
    Mat4 m{};

    float const(*const left)[4] = (float(*)[4]) & a.c0.x;
    float const(*const right)[4] = (float(*)[4]) & b.c0.x;
    float(*result)[4] = (float(*)[4]) & m;

    for (int ii = 0; ii < 4; ++ii) /* column */
    {
        for (int jj = 0; jj < 4; ++jj) /* row */
        {
            for (int kk = 0; kk < 4; ++kk) {
                result[jj][ii] += (left[kk][ii] * right[jj][kk]);
            }
        }
    }
    return m;
}
inline Mat4 MultiplySse(Mat4 const a, Mat4 const b)
{
    __m128 a_r0 = _mm_load_ps(&a.c0.x);
    __m128 a_r1 = _mm_load_ps(&a.c1.x);
    __m128 a_r2 = _mm_load_ps(&a.c2.x);
    __m128 a_r3 = _mm_load_ps(&a.c3.x);

    _MM_TRANSPOSE4_PS(a_r0, a_r1, a_r2, a_r3);

    __m128 const b_c0 = _mm_load_ps(&b.c0.x);
    __m128 const b_c1 = _mm_load_ps(&b.c1.x);
    __m128 const b_c2 = _mm_load_ps(&b.c2.x);
    __m128 const b_c3 = _mm_load_ps(&b.c3.x);

    Mat4 result;
    // c0
    __m128 x = _mm_mul_ps(a_r0, b_c0);
    __m128 y = _mm_mul_ps(a_r1, b_c0);
    __m128 z = _mm_mul_ps(a_r2, b_c0);
    __m128 w = _mm_mul_ps(a_r3, b_c0);

    __m128 t0 = _mm_hadd_ps(x, y);
    __m128 t1 = _mm_hadd_ps(z, w);
    __m128 t2 = _mm_hadd_ps(t0, t1);

    _mm_store_ps(&result.c0.x, t2);

    // c1
    x = _mm_mul_ps(a_r0, b_c1);
    y = _mm_mul_ps(a_r1, b_c1);
    z = _mm_mul_ps(a_r2, b_c1);
    w = _mm_mul_ps(a_r3, b_c1);

    t0 = _mm_hadd_ps(x, y);
    t1 = _mm_hadd_ps(z, w);
    t2 = _mm_hadd_ps(t0, t1);

    _mm_store_ps(&result.c1.x, t2);

    // c2
    x = _mm_mul_ps(a_r0, b_c2);
    y = _mm_mul_ps(a_r1, b_c2);
    z = _mm_mul_ps(a_r2, b_c2);
    w = _mm_mul_ps(a_r3, b_c2);

    t0 = _mm_hadd_ps(x, y);
    t1 = _mm_hadd_ps(z, w);
    t2 = _mm_hadd_ps(t0, t1);

    _mm_store_ps(&result.c2.x, t2);

    // c3
    x = _mm_mul_ps(a_r0, b_c3);
    y = _mm_mul_ps(a_r1, b_c3);
    z = _mm_mul_ps(a_r2, b_c3);
    w = _mm_mul_ps(a_r3, b_c3);

    t0 = _mm_hadd_ps(x, y);
    t1 = _mm_hadd_ps(z, w);
    t2 = _mm_hadd_ps(t0, t1);

    _mm_store_ps(&result.c3.x, t2);

    return result;
}
__forceinline Mat4 MultiplyAvx(Mat4 const& a, Mat4 const& b)
{
    __m256 const a_r0r1 = _mm256_setr_ps(a.c0.x, a.c1.x, a.c2.x, a.c3.x,  //
                                         a.c0.y, a.c1.y, a.c2.y, a.c3.y);
    __m256 const a_r2r3 = _mm256_setr_ps(a.c0.z, a.c1.z, a.c2.z, a.c3.z,  //
                                         a.c0.w, a.c1.w, a.c2.w, a.c3.w);

    __m128 const b_c0_128 = _mm_load_ps(&b.c0.x);
    __m128 const b_c1_128 = _mm_load_ps(&b.c1.x);
    __m128 const b_c2_128 = _mm_load_ps(&b.c2.x);
    __m128 const b_c3_128 = _mm_load_ps(&b.c3.x);

    __m256 const b_c0 = _mm256_setr_m128(b_c0_128, b_c0_128);
    __m256 const b_c1 = _mm256_setr_m128(b_c1_128, b_c1_128);
    __m256 const b_c2 = _mm256_setr_m128(b_c2_128, b_c2_128);
    __m256 const b_c3 = _mm256_setr_m128(b_c3_128, b_c3_128);

    __m256i const mask = _mm256_setr_epi32(0, 1, 4, 5, 2, 3, 6, 7);

    Mat4 result;

    // c0 & c1
    __m256 xy0 = _mm256_mul_ps(a_r0r1, b_c0);
    __m256 zw0 = _mm256_mul_ps(a_r2r3, b_c0);

    __m256 xy1 = _mm256_mul_ps(a_r0r1, b_c1);
    __m256 zw1 = _mm256_mul_ps(a_r2r3, b_c1);

    __m256 t0 = _mm256_hadd_ps(xy0, zw0);
    t0 = _mm256_permutevar8x32_ps(t0, mask);

    __m256 t1 = _mm256_hadd_ps(xy1, zw1);
    t1 = _mm256_permutevar8x32_ps(t1, mask);

    __m256 t2 = _mm256_hadd_ps(t0, t1);
    t2 = _mm256_permutevar8x32_ps(t2, mask);

    _mm256_store_ps(&result.c0.x, t2);

    // c2 & t3
    xy0 = _mm256_mul_ps(a_r0r1, b_c2);
    zw0 = _mm256_mul_ps(a_r2r3, b_c2);

    xy1 = _mm256_mul_ps(a_r0r1, b_c3);
    zw1 = _mm256_mul_ps(a_r2r3, b_c3);

    t0 = _mm256_hadd_ps(xy0, zw0);
    t0 = _mm256_permutevar8x32_ps(t0, mask);

    t1 = _mm256_hadd_ps(xy1, zw1);
    t1 = _mm256_permutevar8x32_ps(t1, mask);

    t2 = _mm256_hadd_ps(t0, t1);
    t2 = _mm256_permutevar8x32_ps(t2, mask);

    _mm256_store_ps(&result.c2.x, t2);

    return result;
}
__forceinline static Mat4 MultiplyAvx512(Mat4 const& in_a, Mat4 const& in_b)
{
#define MAKE_A_MASK(offset)                                                                   \
    _mm512_setr_epi32(0 + (4 * offset), 1 + (4 * offset), 2 + (4 * offset), 3 + (4 * offset), \
                      0 + (4 * offset), 1 + (4 * offset), 2 + (4 * offset), 3 + (4 * offset), \
                      0 + (4 * offset), 1 + (4 * offset), 2 + (4 * offset), 3 + (4 * offset), \
                      0 + (4 * offset), 1 + (4 * offset), 2 + (4 * offset), 3 + (4 * offset))

#define MAKE_B_MASK(offset)                                                                   \
    _mm512_setr_epi32((0 * 4) + offset, (0 * 4) + offset, (0 * 4) + offset, (0 * 4) + offset, \
                      (1 * 4) + offset, (1 * 4) + offset, (1 * 4) + offset, (1 * 4) + offset, \
                      (2 * 4) + offset, (2 * 4) + offset, (2 * 4) + offset, (2 * 4) + offset, \
                      (3 * 4) + offset, (3 * 4) + offset, (3 * 4) + offset, (3 * 4) + offset)

    __m512 const av = _mm512_load_ps(&in_a.c0.x);
    __m512 const bv = _mm512_load_ps(&in_b.c0.x);

    __m512i const am = MAKE_A_MASK(0);
    __m512i const bm = MAKE_B_MASK(0);
    __m512 const a = _mm512_permutexvar_ps(am, av);
    __m512 const b = _mm512_permutexvar_ps(bm, bv);
    __m512 const aa = _mm512_mul_ps(a, b);

    __m512i const cm = MAKE_A_MASK(1);
    __m512i const dm = MAKE_B_MASK(1);
    __m512 const c = _mm512_permutexvar_ps(cm, av);
    __m512 const d = _mm512_permutexvar_ps(dm, bv);
    __m512 const bb = _mm512_fmadd_ps(c, d, aa);

    __m512i const em = MAKE_A_MASK(2);
    __m512i const fm = MAKE_B_MASK(2);
    __m512 const e = _mm512_permutexvar_ps(em, av);
    __m512 const f = _mm512_permutexvar_ps(fm, bv);
    __m512 const cc = _mm512_fmadd_ps(e, f, bb);

    __m512i const gm = MAKE_A_MASK(3);
    __m512i const hm = MAKE_B_MASK(3);
    __m512 const g = _mm512_permutexvar_ps(gm, av);
    __m512 const h = _mm512_permutexvar_ps(hm, bv);
    __m512 const dd = _mm512_fmadd_ps(g, h, cc);

    Mat4 result;
    _mm512_store_ps(&result.c0.x, dd);

    return result;
}
__forceinline Mat4 operator*(Mat4 const& a, Mat4 const& b)
{
    return MultiplyAvx512(a, b);
}
inline void TransposeInPlace(Mat4& m)
{
    _swapf(m.c0.y, m.c1.x);
    _swapf(m.c0.z, m.c2.x);
    _swapf(m.c0.w, m.c3.x);
    _swapf(m.c1.z, m.c2.y);
    _swapf(m.c1.w, m.c3.y);
    _swapf(m.c2.w, m.c3.z);
}
inline Mat4 Transpose(Mat4 m)
{
    TransposeInPlace(m);
    return m;
}

constexpr inline float Determinant(Mat4 const m)
{
    Mat3 const a = {{m.c1.y, m.c1.z, m.c1.w}, {m.c2.y, m.c2.z, m.c2.w}, {m.c3.y, m.c3.z, m.c3.w}};

    Mat3 const b = {{m.c1.x, m.c1.z, m.c1.w}, {m.c2.x, m.c2.z, m.c2.w}, {m.c3.x, m.c3.z, m.c3.w}};

    Mat3 const c = {{m.c1.x, m.c1.y, m.c1.w}, {m.c2.x, m.c2.y, m.c2.w}, {m.c3.x, m.c3.y, m.c3.w}};

    Mat3 const d = {{m.c1.x, m.c1.y, m.c1.z}, {m.c2.x, m.c2.y, m.c2.z}, {m.c3.x, m.c3.y, m.c3.z}};

    float det = 0.0f;
    det += m.c0.x * Determinant(a);
    det -= m.c0.y * Determinant(b);
    det += m.c0.z * Determinant(c);
    det -= m.c0.w * Determinant(d);
    return det;
}

constexpr inline Mat4 operator*(Mat4 const m, float const f)
{
    return {m.c0 * f, m.c1 * f, m.c2 * f, m.c3 * f};
}
inline Mat4 InverseScalar(Mat4 const mat)
{
    float const* const m = &mat.c0.x;

    // build 2x2 determinants
    float const s[] = {
        m[0] * m[5] - m[4] * m[1],  //
        m[0] * m[6] - m[4] * m[2],  //
        m[0] * m[7] - m[4] * m[3],  //
        m[1] * m[6] - m[5] * m[2],  //
        m[1] * m[7] - m[5] * m[3],  //
        m[2] * m[7] - m[6] * m[3],  //
    };

    float const c[] = {
        m[8] * m[13] - m[12] * m[9],    //
        m[8] * m[14] - m[12] * m[10],   //
        m[8] * m[15] - m[12] * m[11],   //
        m[9] * m[14] - m[13] * m[10],   //
        m[9] * m[15] - m[13] * m[11],   //
        m[10] * m[15] - m[14] * m[11],  //
    };

    // Should check for 0 determinant
    float const invdet =
        1.0f / (s[0] * c[5] - s[1] * c[4] + s[2] * c[3] + s[3] * c[2] - s[4] * c[1] + s[5] * c[0]);

    Mat4 ret;
    float* const r = &ret.c0.x;

    r[0] = (m[5] * c[5] - m[6] * c[4] + m[7] * c[3]) * invdet;
    r[1] = (-m[1] * c[5] + m[2] * c[4] - m[3] * c[3]) * invdet;
    r[2] = (m[13] * s[5] - m[14] * s[4] + m[15] * s[3]) * invdet;
    r[3] = (-m[9] * s[5] + m[10] * s[4] - m[11] * s[3]) * invdet;

    r[4] = (-m[4] * c[5] + m[6] * c[2] - m[7] * c[1]) * invdet;
    r[5] = (m[0] * c[5] - m[2] * c[2] + m[3] * c[1]) * invdet;
    r[6] = (-m[12] * s[5] + m[14] * s[2] - m[15] * s[1]) * invdet;
    r[7] = (m[8] * s[5] - m[10] * s[2] + m[11] * s[1]) * invdet;

    r[8] = (m[4] * c[4] - m[5] * c[2] + m[7] * c[0]) * invdet;
    r[9] = (-m[0] * c[4] + m[1] * c[2] - m[3] * c[0]) * invdet;
    r[10] = (m[12] * s[4] - m[13] * s[2] + m[15] * s[0]) * invdet;
    r[11] = (-m[8] * s[4] + m[9] * s[2] - m[11] * s[0]) * invdet;

    r[12] = (-m[4] * c[3] + m[5] * c[1] - m[6] * c[0]) * invdet;
    r[13] = (m[0] * c[3] - m[1] * c[1] + m[2] * c[0]) * invdet;
    r[14] = (-m[12] * s[3] + m[13] * s[1] - m[14] * s[0]) * invdet;
    r[15] = (m[8] * s[3] - m[9] * s[1] + m[10] * s[0]) * invdet;

    return ret;
}

inline Mat4 InverseAvx(Mat4 const mat)
{
    float const* const m = &mat.c0.x;

    // build 2x2 determinants
    float const dets[] = {
        // s
        m[0] * m[5] - m[4] * m[1],  //
        m[0] * m[6] - m[4] * m[2],  //
        m[0] * m[7] - m[4] * m[3],  //
        m[1] * m[6] - m[5] * m[2],  //
        m[1] * m[7] - m[5] * m[3],  //
        m[2] * m[7] - m[6] * m[3],  //

        // c
        m[8] * m[13] - m[12] * m[9],    //
        m[8] * m[14] - m[12] * m[10],   //
        m[8] * m[15] - m[12] * m[11],   //
        m[9] * m[14] - m[13] * m[10],   //
        m[9] * m[15] - m[13] * m[11],   //
        m[10] * m[15] - m[14] * m[11],  //
    };

    // Should check for 0 determinant
    float const det = (dets[0] * dets[11] - dets[1] * dets[10] + dets[2] * dets[9] +
                       dets[3] * dets[8] - dets[4] * dets[7] + dets[5] * dets[6]);
    float const invdet = 1.0f / det;

    // clang-format off
    #if 0
    float* const r = &ret.c0.x;
    r[0] = (+m[5]  * dets[11] - m[6]  * dets[10] + m[7]  * dets[9]) * invdet;
    r[1] = (-m[1]  * dets[11] + m[2]  * dets[10] - m[3]  * dets[9]) * invdet;
    r[2] = (+m[13] * dets[5] - m[14] * dets[4] + m[15] * dets[3]) * invdet;
    r[3] = (-m[9]  * dets[5] + m[10] * dets[4] - m[11] * dets[3]) * invdet;
    r[4] = (-m[4]  * dets[11] + m[6]  * dets[8] - m[7]  * dets[7]) * invdet;
    r[5] = (+m[0]  * dets[11] - m[2]  * dets[8] + m[3]  * dets[7]) * invdet;
    r[6] = (-m[12] * dets[5] + m[14] * dets[2] - m[15] * dets[1]) * invdet;
    r[7] = (+m[8]  * dets[5] - m[10] * dets[2] + m[11] * dets[1]) * invdet;

    r[8]  = (+m[4]  * dets[10] - m[5]  * dets[8] + m[7]  * dets[6]) * invdet;
    r[9]  = (-m[0]  * dets[10] + m[1]  * dets[8] - m[3]  * dets[6]) * invdet;
    r[10] = (+m[12] * dets[4] - m[13] * dets[2] + m[15] * dets[0]) * invdet;
    r[11] = (-m[8]  * dets[4] + m[9]  * dets[2] - m[11] * dets[0]) * invdet;
    r[12] = (-m[4]  * dets[9] + m[5]  * dets[7] - m[6]  * dets[6]) * invdet;
    r[13] = (+m[0]  * dets[9] - m[1]  * dets[7] + m[2]  * dets[6]) * invdet;
    r[14] = (-m[12] * dets[3] + m[13] * dets[1] - m[14] * dets[0]) * invdet;
    r[15] = (+m[8]  * dets[3] - m[9]  * dets[1] + m[10] * dets[0]) * invdet;
    #endif
    // clang-format on

    Mat4 ret;

    __m256 const invdetAvx = _mm256_set1_ps(invdet);
    __m256 const plusMinus = _mm256_setr_ps(0.0f, -0.0f, 0.0f, -0.0f, -0.0f, 0.0f, -0.0f, 0.0f);
    __m256 const minusPlus = _mm256_setr_ps(-0.0f, 0.0f, -0.0f, 0.0f, 0.0f, -0.0f, 0.0f, -0.0f);

    {
        __m256i const aMask = _mm256_setr_epi32(5, 1, 13, 9, 4, 0, 12, 8);
        __m256 a = _mm256_i32gather_ps(m, aMask, 4);
        a = _mm256_xor_ps(plusMinus, a);

        __m256i const bMask = _mm256_setr_epi32(6, 2, 14, 10, 6, 2, 14, 10);
        __m256 b = _mm256_i32gather_ps(m, bMask, 4);
        b = _mm256_xor_ps(minusPlus, b);

        __m256i const cMask = _mm256_setr_epi32(7, 3, 15, 11, 7, 3, 15, 11);
        __m256 c = _mm256_i32gather_ps(m, cMask, 4);
        c = _mm256_xor_ps(plusMinus, c);

        __m256i const daMask = _mm256_setr_epi32(11, 11, 5, 5, 11, 11, 5, 5);
        __m256 da = _mm256_i32gather_ps(dets, daMask, 4);
        __m256i const dbMask = _mm256_setr_epi32(10, 10, 4, 4, 8, 8, 2, 2);
        __m256 db = _mm256_i32gather_ps(dets, dbMask, 4);
        __m256i const dcMask = _mm256_setr_epi32(9, 9, 3, 3, 7, 7, 1, 1);
        __m256 dc = _mm256_i32gather_ps(dets, dcMask, 4);

        __m256 c0c1 = _mm256_mul_ps(a, da);
        c0c1 = _mm256_add_ps(c0c1, _mm256_mul_ps(b, db));
        c0c1 = _mm256_add_ps(c0c1, _mm256_mul_ps(c, dc));

        c0c1 = _mm256_mul_ps(_mm256_set1_ps(invdet), c0c1);
        _mm256_store_ps(&ret.c0.x, c0c1);
    }

    {
        __m256i const aMask = _mm256_setr_epi32(4, 0, 12, 8, 4, 0, 12, 8);
        __m256 a = _mm256_i32gather_ps(m, aMask, 4);
        a = _mm256_xor_ps(plusMinus, a);

        __m256i const bMask = _mm256_setr_epi32(5, 1, 13, 9, 5, 1, 13, 9);
        __m256 b = _mm256_i32gather_ps(m, bMask, 4);
        b = _mm256_xor_ps(minusPlus, b);

        __m256i const cMask = _mm256_setr_epi32(7, 3, 15, 11, 6, 2, 14, 10);
        __m256 c = _mm256_i32gather_ps(m, cMask, 4);
        c = _mm256_xor_ps(plusMinus, c);

        __m256i const daMask = _mm256_setr_epi32(10, 10, 4, 4, 9, 9, 3, 3);
        __m256 da = _mm256_i32gather_ps(dets, daMask, 4);
        __m256i const dbMask = _mm256_setr_epi32(8, 8, 2, 2, 7, 7, 1, 1);
        __m256 db = _mm256_i32gather_ps(dets, dbMask, 4);
        __m256i const dcMask = _mm256_setr_epi32(6, 6, 0, 0, 6, 6, 0, 0);
        __m256 dc = _mm256_i32gather_ps(dets, dcMask, 4);

        __m256 c2c3 = _mm256_mul_ps(a, da);
        c2c3 = _mm256_add_ps(c2c3, _mm256_mul_ps(b, db));
        c2c3 = _mm256_add_ps(c2c3, _mm256_mul_ps(c, dc));
        c2c3 = _mm256_mul_ps(invdetAvx, c2c3);

        _mm256_store_ps(&ret.c2.x, c2c3);
    }

    return ret;
}

inline Mat4 Inverse(Mat4 const m)
{
#if 1
    return InverseScalar(m);
#else
    // TODO: AVX works in Debug, but not in Release
    return InverseAvx(m);
#endif
}

inline Vec4 operator*(Mat4 m, Vec4 const v)
{
    TransposeInPlace(m);
    return {
        Hadd(m.c0 * v),
        Hadd(m.c1 * v),
        Hadd(m.c2 * v),
        Hadd(m.c3 * v),
    };
}

}  // namespace ak
