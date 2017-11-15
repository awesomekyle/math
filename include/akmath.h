#pragma once
#include <math.h>

namespace ak {

struct Vec2
{
    float x;
    float y;
};

// Vec2 math
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

constexpr inline Vec2 operator*(Vec2 const a, float const b)
{
    return {a.x * b, a.y * b};
}
constexpr inline Vec2 operator/(Vec2 const a, float const b)
{
    return {a.x / b, a.y / b};
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

}  // namespace ak
