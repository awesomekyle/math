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

struct Mat4
{
    Vec4 c0;
    Vec4 c1;
    Vec4 c2;
    Vec4 c3;

    inline static Mat4 Identity();
    inline static Mat4 Scaling(float const x, float const y, float const z);
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
inline float Hadd(Vec3 const v)
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

inline float Hadd(Vec4 const v)
{
    return v.x + v.y + v.z + v.w;
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
inline Mat3 operator*(Mat3 const a, Mat3 const b)
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

inline float Determinant(Mat3 const m)
{
    float const f0 = m.c0.x * (m.c1.y * m.c2.z - m.c2.y * m.c1.z);
    float const f1 = m.c0.y * -(m.c1.x * m.c2.z - m.c2.x * m.c1.z);
    float const f2 = m.c0.z * (m.c1.x * m.c2.y - m.c2.x * m.c1.y);
    return f0 + f1 + f2;
}

inline Mat3 operator*(Mat3 const m, float const f)
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
inline Mat4 Mat4::Identity()
{
    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
}
inline Mat4 Mat4::Scaling(float const x, float const y, float const z)
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
inline Mat4 operator*(Mat4 const a, Mat4 const b)
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

inline float Determinant(Mat4 const m)
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

inline Mat4 operator*(Mat4 const m, float const f)
{
    return {m.c0 * f, m.c1 * f, m.c2 * f, m.c3 * f};
}
inline Mat4 Inverse(Mat4 mat)
{
    /* row 1 */
    Mat3 a{{mat.c1.y, mat.c1.z, mat.c1.w},
           {mat.c2.y, mat.c2.z, mat.c2.w},
           {mat.c3.y, mat.c3.z, mat.c3.w}};

    Mat3 b{{mat.c1.x, mat.c1.z, mat.c1.w},
           {mat.c2.x, mat.c2.z, mat.c2.w},
           {mat.c3.x, mat.c3.z, mat.c3.w}};

    Mat3 c{{mat.c1.x, mat.c1.y, mat.c1.w},
           {mat.c2.x, mat.c2.y, mat.c2.w},
           {mat.c3.x, mat.c3.y, mat.c3.w}};

    Mat3 d{{mat.c1.x, mat.c1.y, mat.c1.z},
           {mat.c2.x, mat.c2.y, mat.c2.z},
           {mat.c3.x, mat.c3.y, mat.c3.z}};

    /* row 2 */
    Mat3 e{{mat.c0.y, mat.c0.z, mat.c0.w},
           {mat.c2.y, mat.c2.z, mat.c2.w},
           {mat.c3.y, mat.c3.z, mat.c3.w}};

    Mat3 f{{mat.c0.x, mat.c0.z, mat.c0.w},
           {mat.c2.x, mat.c2.z, mat.c2.w},
           {mat.c3.x, mat.c3.z, mat.c3.w}};

    Mat3 g{{mat.c0.x, mat.c0.y, mat.c0.w},
           {mat.c2.x, mat.c2.y, mat.c2.w},
           {mat.c3.x, mat.c3.y, mat.c3.w}};

    Mat3 h{{mat.c0.x, mat.c0.y, mat.c0.z},
           {mat.c2.x, mat.c2.y, mat.c2.z},
           {mat.c3.x, mat.c3.y, mat.c3.z}};

    /* row 3 */
    Mat3 i{{mat.c0.y, mat.c0.z, mat.c0.w},
           {mat.c1.y, mat.c1.z, mat.c1.w},
           {mat.c3.y, mat.c3.z, mat.c3.w}};

    Mat3 j{{mat.c0.x, mat.c0.z, mat.c0.w},
           {mat.c1.x, mat.c1.z, mat.c1.w},
           {mat.c3.x, mat.c3.z, mat.c3.w}};

    Mat3 k{{mat.c0.x, mat.c0.y, mat.c0.w},
           {mat.c1.x, mat.c1.y, mat.c1.w},
           {mat.c3.x, mat.c3.y, mat.c3.w}};

    Mat3 l{{mat.c0.x, mat.c0.y, mat.c0.z},
           {mat.c1.x, mat.c1.y, mat.c1.z},
           {mat.c3.x, mat.c3.y, mat.c3.z}};

    /* row 4 */
    Mat3 m{{mat.c0.y, mat.c0.z, mat.c0.w},
           {mat.c1.y, mat.c1.z, mat.c1.w},
           {mat.c2.y, mat.c2.z, mat.c2.w}};

    Mat3 n{{mat.c0.x, mat.c0.z, mat.c0.w},
           {mat.c1.x, mat.c1.z, mat.c1.w},
           {mat.c2.x, mat.c2.z, mat.c2.w}};

    Mat3 o{{mat.c0.x, mat.c0.y, mat.c0.w},
           {mat.c1.x, mat.c1.y, mat.c1.w},
           {mat.c2.x, mat.c2.y, mat.c2.w}};

    Mat3 p{{mat.c0.x, mat.c0.y, mat.c0.z},
           {mat.c1.x, mat.c1.y, mat.c1.z},
           {mat.c2.x, mat.c2.y, mat.c2.z}};

    /* row 1 */
    Mat4 ret = {
        {
            Determinant(a),
            -Determinant(b),
            Determinant(c),
            -Determinant(d),
        },
        {
            -Determinant(e),
            Determinant(f),
            -Determinant(g),
            Determinant(h),
        },
        {
            Determinant(i),
            -Determinant(j),
            Determinant(k),
            -Determinant(l),
        },
        {
            -Determinant(m),
            Determinant(n),
            -Determinant(o),
            Determinant(p),
        },
    };

    TransposeInPlace(ret);
    float const recip = 1.0f / Determinant(mat);
    ret = ret * recip;
    return ret;
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
