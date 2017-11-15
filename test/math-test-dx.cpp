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

DirectX::XMVECTOR XmFromAk(const ak::Vec2& v)
{
    return DirectX::XMVectorSet(v.x, v.y, 0.0f, 0.0f);
}

bool operator==(const DirectX::XMVECTOR& x, const ak::Vec2& k)
{
    return DirectX::XMVectorGetX(x) == k.x && DirectX::XMVectorGetY(x) == k.y;
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
    }
}
