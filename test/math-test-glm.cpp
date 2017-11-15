#include "akmath.h"
#include "catch-output.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <catch.hpp>

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

// mat3
glm::mat3 GlmFromAk(const ak::Mat3& m)
{
    return glm::mat3{m.c0.x, m.c0.y, m.c0.z,  //
                     m.c1.x, m.c1.y, m.c1.z,  //
                     m.c2.x, m.c2.y, m.c2.z};
}
inline bool operator==(const glm::mat3 g, const ak::Mat3& k)
{
    float const* const pX = &g[0][0];
    float const* const pK = &k.c0.x;
    for (int ii = 0; ii < sizeof(k) / sizeof(k.c0.x); ++ii) {
        if (pX[ii] != Approx(pK[ii])) {
            return false;
        }
    }
    return true;
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

TEST_CASE("GLM - mat3 arithmatic", "[mat3]")
{
    ak::Mat3 const i = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
    };
    ak::Mat3 const j = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
    };
    ak::Mat3 const k = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
    };

    glm::mat3 const a = GlmFromAk(i);
    glm::mat3 const b = GlmFromAk(j);
    glm::mat3 const c = GlmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("identity")
    {
        CHECK(glm::mat3() == ak::Mat3::Identity());
    }

    SECTION("scale")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        CHECK(glm::scale(glm::mat4(), {x, y, z}) == ak::Mat3::Scaling(x, y, z));
    }

    SECTION("rotation")
    {
        float const r = RandFloat(-50.0f, 50.0f);
        CHECK(glm::rotate(glm::mat4(), r, {1, 0, 0}) == ak::Mat3::RotationX(r));
        CHECK(glm::rotate(glm::mat4(), r, {0, 1, 0}) == ak::Mat3::RotationY(r));
        CHECK(glm::rotate(glm::mat4(), r, {0, 0, 1}) == ak::Mat3::RotationZ(r));
    }
    SECTION("axis rotation")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        auto const glmRotation = (glm::mat3)glm::rotate(glm::mat4(), scalar, {x, y, z});
        CHECK(glmRotation == ak::Mat3::RotationAxis({x, y, z}, scalar));
    }
    SECTION("multiplication")
    {
        auto const m1 = a * b;
        auto const m2 = i * j;
        CHECK(m1 == m2);
    }
    SECTION("transpose")
    {
        REQUIRE(glm::transpose(a) == ak::Transpose(i));
    }
    SECTION("determinant")
    {
        REQUIRE(glm::determinant(a) == Approx(ak::Determinant(i)));
    }
    SECTION("inverse")
    {
        REQUIRE(glm::inverse(a) == ak::Inverse(i));
    }
    SECTION("vector multiplication")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);

        glm::vec3 const u{x, y, z};
        ak::Vec3 const v{x, y, z};
        REQUIRE(u == v);

        CHECK(a * u == i * v);
    }
}
