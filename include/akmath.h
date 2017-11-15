#pragma once
#include <math.h>

namespace ak {

struct Vec2
{
    float x;
    float y;
};

// Vec2 math
constexpr inline Vec2 operator+(const Vec2& a, const Vec2& b)
{
    return {a.x + b.x, a.y + b.y};
}
constexpr inline Vec2 operator-(const Vec2& a, const Vec2& b)
{
    return {a.x - b.x, a.y - b.y};
}
constexpr inline Vec2 operator*(const Vec2& a, const Vec2& b)
{
    return {a.x * b.x, a.y * b.y};
}
constexpr inline Vec2 operator/(const Vec2& a, const Vec2& b)
{
    return {a.x / b.x, a.y / b.y};
}

constexpr inline Vec2 operator*(const Vec2& a, float const b)
{
    return {a.x * b, a.y * b};
}
constexpr inline Vec2 operator/(const Vec2& a, float const b)
{
    return {a.x / b, a.y / b};
}

// Vec2 misc
inline float LengthSq(const Vec2& a)
{
    return a.x * a.x + a.y * a.y;
}
inline float Length(const Vec2& a)
{
    return sqrtf(LengthSq(a));
}
inline float DistanceSq(const Vec2& a, const Vec2& b)
{
    return LengthSq(a - b);
}
inline float Distance(const Vec2& a, const Vec2& b)
{
    return sqrtf(DistanceSq(a, b));
}

}  // namespace ak
