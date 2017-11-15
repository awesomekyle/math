#include "akmath.h"
#include <catch.hpp>
#include <glm/glm.hpp>

namespace glm {

template<typename T>
inline T lerp(T const& a, T const& b, float const t)
{
    return a + (b - a) * t;
}

}  // namespace glm

namespace {

float RandFloat(float const min, float const max)
{
    float f = rand() / static_cast<float>(RAND_MAX);
    f *= (max - min);
    return f + min;
}

// vec2
glm::vec2 GlmFromAk(const ak::Vec2& v)
{
    return {
        v.x,
        v.y,
    };
}

inline bool operator==(const glm::vec2& g, const ak::Vec2& k)
{
    return g.x == Approx(k.x) && g.y == Approx(k.y);
}
inline bool operator==(const ak::Vec2& k, const glm::vec2& g)
{
    return g == k;
}

// vec3
glm::vec3 GlmFromAk(const ak::Vec3& v)
{
    return {v.x, v.y, v.z};
}

inline bool operator==(const glm::vec3& g, const ak::Vec3& k)
{
    return g.x == Approx(k.x) && g.y == Approx(k.y) && g.z == Approx(k.z);
}
inline bool operator==(const ak::Vec3& k, const glm::vec3& g)
{
    return g == k;
}

// vec4
glm::vec4 GlmFromAk(const ak::Vec4& v)
{
    return {v.x, v.y, v.z, v.w};
}

inline bool operator==(const glm::vec4& g, const ak::Vec4& k)
{
    return g.x == Approx(k.x) && g.y == Approx(k.y) && g.z == Approx(k.z) && g.w == Approx(k.w);
}
inline bool operator==(const ak::Vec4& k, const glm::vec4& g)
{
    return g == k;
}

}  // namespace

TEST_CASE("GLM - vec2 arithmatic", "[vec2]")
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

    auto const a = GlmFromAk(i);
    auto const b = GlmFromAk(j);
    auto const c = GlmFromAk(k);
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
        REQUIRE(glm::length(a) == ak::Length(i));
        REQUIRE(glm::length(b) * glm::length(b) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(glm::distance(a, b) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(glm::normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(glm::min(a, b) == ak::Min(i, j));
        REQUIRE(glm::max(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(glm::lerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }
}

TEST_CASE("GLM - vec3 arithmatic", "[vec3]")
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

    auto const a = GlmFromAk(i);
    auto const b = GlmFromAk(j);
    auto const c = GlmFromAk(k);
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
        REQUIRE(glm::length(a) == ak::Length(i));
        REQUIRE(glm::length(b) * glm::length(b) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(glm::distance(a, b) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(glm::normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(glm::min(a, b) == ak::Min(i, j));
        REQUIRE(glm::max(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(glm::lerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }

    SECTION("dot")
    {
        REQUIRE(glm::dot(a, b) == ak::Dot(i, j));
    }

    SECTION("cross")
    {
        REQUIRE(glm::cross(a, b) == ak::Cross(i, j));
    }
}

TEST_CASE("GLM - vec4 arithmatic", "[vec4]")
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

    auto const a = GlmFromAk(i);
    auto const b = GlmFromAk(j);
    auto const c = GlmFromAk(k);
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
        REQUIRE(glm::length(a) == ak::Length(i));
        REQUIRE(glm::length(b) * glm::length(b) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(glm::distance(a, b) == ak::Distance(i, j));
        REQUIRE(ak::Distance(j, k) == ak::Distance(k, j));
    }
    SECTION("normalize")
    {
        REQUIRE(glm::normalize(a) == ak::Normalize(i));
    }

    SECTION("min max")
    {
        REQUIRE(glm::min(a, b) == ak::Min(i, j));
        REQUIRE(glm::max(a, b) == ak::Max(i, j));
    }

    SECTION("lerp")
    {
        float const f = RandFloat(0.0f, 1.0f);
        REQUIRE(glm::lerp(a, b, f) == ak::Lerp(i, j, f));
    }

    SECTION("negate")
    {
        REQUIRE(-a == -i);
    }
}
