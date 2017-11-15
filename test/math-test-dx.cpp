#include "akmath.h"
#include <catch.hpp>
#include <DirectXMath.h>

using namespace DirectX;

namespace {

float RandFloat(float const min, float const max)
{
    float f = rand() / static_cast<float>(RAND_MAX);
    f *= (max - min);
    return f + min;
}

// vec2
DirectX::XMVECTOR XmFromAk(const ak::Vec2& v)
{
    return DirectX::XMVectorSet(v.x, v.y, 0.0f, 0.0f);
}

inline bool operator==(const DirectX::XMVECTOR& x, const ak::Vec2& k)
{
    return DirectX::XMVectorGetX(x) == k.x && DirectX::XMVectorGetY(x) == k.y;
}
inline bool operator==(const ak::Vec2& k, const DirectX::XMVECTOR& x)
{
    return x == k;
}

// vec3
DirectX::XMVECTOR XmFromAk(const ak::Vec3& v)
{
    return DirectX::XMVectorSet(v.x, v.y, v.z, 0.0f);
}

inline bool operator==(const DirectX::XMVECTOR& x, const ak::Vec3& k)
{
    return DirectX::XMVectorGetX(x) == k.x && DirectX::XMVectorGetY(x) == k.y &&
           DirectX::XMVectorGetZ(x) == k.z;
}
inline bool operator==(const ak::Vec3& k, const DirectX::XMVECTOR& x)
{
    return x == k;
}

// vec4
DirectX::XMVECTOR XmFromAk(const ak::Vec4& v)
{
    return DirectX::XMVectorSet(v.x, v.y, v.z, v.w);
}

inline bool operator==(const DirectX::XMVECTOR& x, const ak::Vec4& k)
{
    return DirectX::XMVectorGetX(x) == Approx(k.x) && DirectX::XMVectorGetY(x) == Approx(k.y) &&
           DirectX::XMVectorGetZ(x) == Approx(k.z) && DirectX::XMVectorGetW(x) == Approx(k.w);
}
inline bool operator==(const ak::Vec4& k, const DirectX::XMVECTOR& x)
{
    return x == k;
}

}  // namespace

TEST_CASE("vec2 creation", "[vec2]")
{
    // default construction
    {
        ak::Vec2 vec;
        (void)vec;
    }

    // intializer list
    {
        ak::Vec2 const vec = {14, 3};
        REQUIRE(vec.x == 14);
        REQUIRE(vec.y == 3);
    }

    // C++11 intializer list
    {
        ak::Vec2 const vec{14, 3};
        REQUIRE(vec.x == 14);
        REQUIRE(vec.y == 3);
    }

    // constexpr initialization
    {
        constexpr ak::Vec2 vec{14, 3};
        REQUIRE(vec.x == 14);
        REQUIRE(vec.y == 3);
    }

    // zero
    {
        auto const x = DirectX::XMVectorZero();
        ak::Vec2 const k{};
        REQUIRE(x == k);
    }
}

TEST_CASE("vec2 arithmatic", "[vec2]")
{
    ak::Vec2 const i = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec2 const j = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec2 const k = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };

    DirectX::XMVECTOR const a = XmFromAk(i);
    DirectX::XMVECTOR const b = XmFromAk(j);
    DirectX::XMVECTOR const c = XmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("plus")
    {
        auto const x = a + b;
        auto const y = i + j;
        REQUIRE(x == y);
    }
    SECTION("minus")
    {
        auto const x = a - b;
        auto const y = i - j;
        REQUIRE(x == y);
    }
    SECTION("times")
    {
        auto const x = a * b;
        auto const y = i * j;
        REQUIRE(x == y);
    }
    SECTION("divide")
    {
        auto const x = a / b;
        auto const y = i / j;
        REQUIRE(x == y);
    }

    SECTION("times scalar")
    {
        auto const x = a * scalar;
        auto const y = i * scalar;
        REQUIRE(x == y);
    }
    SECTION("divide scalar")
    {
        auto const x = a / scalar;
        auto const y = i / scalar;
        REQUIRE(x == y);
    }

    SECTION("length")
    {
        REQUIRE(XMVectorGetX(XMVector2Length(a)) == ak::Length(i));
        REQUIRE(XMVectorGetX(XMVector2LengthSq(b)) == ak::LengthSq(j));
    }
    SECTION("distance")
    {
        REQUIRE(XMVectorGetX(XMVector2Length(a - b)) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(XMVector2Normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(XMVectorMin(a, b) == ak::Min(i, j));
        REQUIRE(XMVectorMax(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(XMVectorLerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }
}

TEST_CASE("vec3 arithmatic", "[vec3]")
{
    ak::Vec3 const i = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec3 const j = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec3 const k = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };

    DirectX::XMVECTOR const a = XmFromAk(i);
    DirectX::XMVECTOR const b = XmFromAk(j);
    DirectX::XMVECTOR const c = XmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("plus")
    {
        auto const x = a + b;
        auto const y = i + j;
        REQUIRE(x == y);
    }
    SECTION("minus")
    {
        auto const x = a - b;
        auto const y = i - j;
        REQUIRE(x == y);
    }
    SECTION("times")
    {
        auto const x = a * b;
        auto const y = i * j;
        REQUIRE(x == y);
    }
    SECTION("divide")
    {
        auto const x = a / b;
        auto const y = i / j;
        REQUIRE(x == y);
    }

    SECTION("times scalar")
    {
        auto const x = a * scalar;
        auto const y = i * scalar;
        REQUIRE(x == y);
    }
    SECTION("divide scalar")
    {
        auto const x = a / scalar;
        auto const y = i / scalar;
        REQUIRE(x == y);
    }

    SECTION("length")
    {
        REQUIRE(XMVectorGetX(XMVector3Length(a)) == ak::Length(i));
        REQUIRE(XMVectorGetX(XMVector3LengthSq(b)) == ak::LengthSq(j));
    }
    SECTION("distance")
    {
        REQUIRE(XMVectorGetX(XMVector3Length(a - b)) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(XMVector3Normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(XMVectorMin(a, b) == ak::Min(i, j));
        REQUIRE(XMVectorMax(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(XMVectorLerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }

    SECTION("dot")
    {
        REQUIRE(XMVectorGetX(XMVector3Dot(a, b)) == ak::Dot(i, j));
    }

    SECTION("cross")
    {
        REQUIRE(XMVector3Cross(a, b) == ak::Cross(i, j));
    }
}

TEST_CASE("vec4 arithmatic", "[vec4]")
{
    ak::Vec4 const i = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec4 const j = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };
    ak::Vec4 const k = {
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f),
    };

    DirectX::XMVECTOR const a = XmFromAk(i);
    DirectX::XMVECTOR const b = XmFromAk(j);
    DirectX::XMVECTOR const c = XmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("plus")
    {
        auto const x = a + b;
        auto const y = i + j;
        REQUIRE(x == y);
    }
    SECTION("minus")
    {
        auto const x = a - b;
        auto const y = i - j;
        REQUIRE(x == y);
    }
    SECTION("times")
    {
        auto const x = a * b;
        auto const y = i * j;
        REQUIRE(x == y);
    }
    SECTION("divide")
    {
        auto const x = a / b;
        auto const y = i / j;
        REQUIRE(x == y);
    }

    SECTION("times scalar")
    {
        auto const x = a * scalar;
        auto const y = i * scalar;
        REQUIRE(x == y);
    }
    SECTION("divide scalar")
    {
        auto const x = a / scalar;
        auto const y = i / scalar;
        REQUIRE(x == y);
    }

    SECTION("length")
    {
        REQUIRE(XMVectorGetX(XMVector4Length(a)) == ak::Length(i));
        REQUIRE(XMVectorGetX(XMVector4LengthSq(b)) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(XMVectorGetX(XMVector4Length(a - b)) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(XMVector4Normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(XMVectorMin(a, b) == ak::Min(i, j));
        REQUIRE(XMVectorMax(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(XMVectorLerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }
}
