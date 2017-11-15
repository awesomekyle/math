#include "akmath.h"
#include <iostream>
#include <DirectXMath.h>

namespace DirectX {

std::ostream& operator<<(std::ostream& os, XMMATRIX const& value)
{
    float const(*const pValue)[4] = (float(*)[4]) & value;
    os << "{ " << pValue[0][0] << ", " << pValue[0][1] << ", " << pValue[0][2] << ", "
       << pValue[0][3] << " }\n";
    os << "{ " << pValue[1][0] << ", " << pValue[1][1] << ", " << pValue[1][2] << ", "
       << pValue[1][3] << " }\n";
    os << "{ " << pValue[2][0] << ", " << pValue[2][1] << ", " << pValue[2][2] << ", "
       << pValue[2][3] << " }\n";
    os << "{ " << pValue[3][0] << ", " << pValue[3][1] << ", " << pValue[3][2] << ", "
       << pValue[3][3] << " }";
    return os;
}
}  // namespace DirectX

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
}
