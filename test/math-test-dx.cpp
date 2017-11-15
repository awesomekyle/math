#include "akmath.h"
#include "catch-output.h"

#include <iostream>
#include <DirectXMath.h>

#include <catch.hpp>

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
    return DirectX::XMVectorGetX(x) == Approx(k.x) && DirectX::XMVectorGetY(x) == Approx(k.y) &&
           DirectX::XMVectorGetZ(x) == Approx(k.z);
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

// mat3
DirectX::XMMATRIX XmFromAk(const ak::Mat3& m)
{
    return XMMatrixSet(m.c0.x, m.c0.y, m.c0.z, 0.0f,  //
                       m.c1.x, m.c1.y, m.c1.z, 0.0f,  //
                       m.c2.x, m.c2.y, m.c2.z, 0.0f,  //
                       0.0f, 0.0f, 0.0f, 1.0f);
}
inline bool operator==(const DirectX::XMMATRIX& x, const ak::Mat3& k)
{
    XMFLOAT3X3 xmFloat = {};
    XMStoreFloat3x3(&xmFloat, x);

    float const* const pX = &xmFloat._11;
    float const* const pK = &k.c0.x;
    for (int ii = 0; ii < sizeof(k) / sizeof(k.c0.x); ++ii) {
        if (pX[ii] != Approx(pK[ii])) {
            return false;
        }
    }
    return true;
}

// mat4
DirectX::XMMATRIX XmFromAk(const ak::Mat4& m)
{
    return XMMatrixSet(m.c0.x, m.c0.y, m.c0.z, m.c0.w,  //
                       m.c1.x, m.c1.y, m.c1.z, m.c1.w,  //
                       m.c2.x, m.c2.y, m.c2.z, m.c2.w,  //
                       m.c3.x, m.c3.y, m.c3.z, m.c3.w);
}
inline bool operator==(const DirectX::XMMATRIX& x, const ak::Mat4& k)
{
    XMFLOAT4X4 xmFloat = {};
    XMStoreFloat4x4(&xmFloat, x);

    float const* const pX = &xmFloat._11;
    float const* const pK = &k.c0.x;
    constexpr int numFloats = sizeof(k) / sizeof(k.c0.x);
    for (int ii = 0; ii < numFloats; ++ii) {
        if (pX[ii] != Approx(pK[ii])) {
            return false;
        }
    }
    return true;
}

}  // namespace

TEST_CASE("DirectXMath - vec2 arithmatic", "[vec2]")
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

TEST_CASE("DirectXMath - vec3 arithmatic", "[vec3]")
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
        REQUIRE(XMVectorGetX(XMVector3Length(a)) == Approx(ak::Length(i)));
        REQUIRE(XMVectorGetX(XMVector3LengthSq(b)) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(XMVectorGetX(XMVector3Length(a - b)) == Approx(ak::Distance(i, j)));
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

TEST_CASE("DirectXMath - vec4 arithmatic", "[vec4]")
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
        REQUIRE(XMVectorGetX(XMVector4Length(a)) == Approx(ak::Length(i)));
        REQUIRE(XMVectorGetX(XMVector4LengthSq(b)) == Approx(ak::LengthSq(j)));
    }
    SECTION("distance")
    {
        REQUIRE(XMVectorGetX(XMVector4Length(a - b)) == Approx(ak::Distance(i, j)));
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

TEST_CASE("DirectXMath - mat3 arithmatic", "[mat3]")
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

    DirectX::XMMATRIX const a = XmFromAk(i);
    DirectX::XMMATRIX const b = XmFromAk(j);
    DirectX::XMMATRIX const c = XmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("identity")
    {
        REQUIRE(XMMatrixIdentity() == ak::Mat3::Identity());
    }

    SECTION("scale")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        REQUIRE(XMMatrixScaling(x, y, z) == ak::Mat3::Scaling(x, y, z));
    }

    SECTION("rotation")
    {
        float const r = RandFloat(-50.0f, 50.0f);
        REQUIRE(XMMatrixRotationX(r) == ak::Mat3::RotationX(r));
        REQUIRE(XMMatrixRotationY(r) == ak::Mat3::RotationY(r));
        REQUIRE(XMMatrixRotationZ(r) == ak::Mat3::RotationZ(r));
    }
    SECTION("axis rotation")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        auto const xmRotation = XMMatrixRotationAxis(XMVectorSet(x, y, z, 0), scalar);
        REQUIRE(xmRotation == ak::Mat3::RotationAxis({x, y, z}, scalar));
    }
    SECTION("multiplication")
    {
        auto const m1 = b * a;
        auto const m2 = i * j;
        REQUIRE(m1 == m2);
    }
    SECTION("transpose")
    {
        REQUIRE(XMMatrixTranspose(a) == ak::Transpose(i));
    }
    SECTION("determinant")
    {
        REQUIRE(XMVectorGetX(XMMatrixDeterminant(a)) == Approx(ak::Determinant(i)));
    }
    SECTION("inverse")
    {
        REQUIRE(XMMatrixInverse(nullptr, a) == ak::Inverse(i));
    }
    SECTION("vector multiplication")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);

        XMVECTOR const u = XMVectorSet(x, y, z, 0);
        ak::Vec3 const v{x, y, z};
        REQUIRE(u == v);

        CHECK(XMVector3Transform(u, a) == i * v);
    }
}

TEST_CASE("DirectXMath - mat4 arithmatic", "[mat4]")
{
    ak::Mat4 const i = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
    };
    ak::Mat4 const j = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
    };
    ak::Mat4 const k = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
    };

    DirectX::XMMATRIX const a = XmFromAk(i);
    DirectX::XMMATRIX const b = XmFromAk(j);
    DirectX::XMMATRIX const c = XmFromAk(k);
    float const scalar = RandFloat(-50.0f, 50.0f);

    REQUIRE(a == i);
    REQUIRE(b == j);
    REQUIRE(c == k);

    SECTION("identity")
    {
        REQUIRE(XMMatrixIdentity() == ak::Mat4::Identity());
    }

    SECTION("scale")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        REQUIRE(XMMatrixScaling(x, y, z) == ak::Mat4::Scaling(x, y, z));
    }

    SECTION("rotation")
    {
        float const r = RandFloat(-50.0f, 50.0f);
        REQUIRE(XMMatrixRotationX(r) == ak::Mat4::RotationX(r));
        REQUIRE(XMMatrixRotationY(r) == ak::Mat4::RotationY(r));
        REQUIRE(XMMatrixRotationZ(r) == ak::Mat4::RotationZ(r));
    }
    SECTION("axis rotation")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        auto const xmRotation = XMMatrixRotationAxis(XMVectorSet(x, y, z, 0), scalar);
        REQUIRE(xmRotation == ak::Mat4::RotationAxis({x, y, z}, scalar));
    }
    SECTION("multiplication")
    {
        auto const m1 = b * a;
        auto const m2 = i * j;
        REQUIRE(m1 == m2);
    }
    SECTION("transpose")
    {
        REQUIRE(XMMatrixTranspose(a) == ak::Transpose(i));
    }
    SECTION("determinant")
    {
        REQUIRE(XMVectorGetX(XMMatrixDeterminant(a)) == Approx(ak::Determinant(i)));
    }
    SECTION("inverse")
    {
        REQUIRE(XMMatrixInverse(nullptr, a) == ak::Inverse(i));
    }
    SECTION("vector multiplication")
    {
        float const x = RandFloat(-50.0f, 50.0f);
        float const y = RandFloat(-50.0f, 50.0f);
        float const z = RandFloat(-50.0f, 50.0f);
        float const w = RandFloat(-50.0f, 50.0f);

        XMVECTOR const u = XMVectorSet(x, y, z, w);
        ak::Vec4 const v{x, y, z, w};
        REQUIRE(u == v);

        CHECK(XMVector4Transform(u, a) == i * v);
    }
}
