#include "akmath.h"
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <DirectXMath.h>

namespace {

using namespace DirectX;
using namespace ak;

enum {
    kLoopCount = 128,
};

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
DirectX::XMVECTOR XmFromAk(const ak::Vec3& v)
{
    return DirectX::XMVectorSet(v.x, v.y, v.z, 0.0f);
}
DirectX::XMVECTOR XmFromAk(const ak::Vec4& v)
{
    return DirectX::XMVectorSet(v.x, v.y, v.z, v.w);
}

// DX
void FillVec(DirectX::XMVECTOR& v)
{
    v = XMVectorSet(RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f));
}

// GLM
void FillVec(glm::vec2& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(glm::vec3& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(glm::vec4& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)};
}

// AK
void FillVec(ak::Vec2& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(ak::Vec3& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(ak::Vec4& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)};
}

//-----------------------------------------------------------------------------
template<class Vector>
void VecAddition(benchmark::State& state)
{
    Vector a, b;
    FillVec(a);
    FillVec(b);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize(a + b);
        }
    }
}
template<class Vector>
void VecSubtraction(benchmark::State& state)
{
    Vector a, b;
    FillVec(a);
    FillVec(b);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize(a - b);
        }
    }
}
template<class Vector>
void VecMultiplication(benchmark::State& state)
{
    Vector a, b;
    FillVec(a);
    FillVec(b);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize(a * b);
        }
    }
}

template<class Vector>
void VecDivision(benchmark::State& state)
{
    Vector a, b;
    FillVec(a);
    FillVec(b);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize(a / b);
        }
    }
}

BENCHMARK_TEMPLATE(VecAddition, XMVECTOR);
BENCHMARK_TEMPLATE(VecAddition, glm::vec2);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec2);

BENCHMARK_TEMPLATE(VecAddition, glm::vec3);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec3);

BENCHMARK_TEMPLATE(VecAddition, glm::vec4);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec4);

BENCHMARK_TEMPLATE(VecSubtraction, XMVECTOR);
BENCHMARK_TEMPLATE(VecSubtraction, glm::vec2);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec2);

BENCHMARK_TEMPLATE(VecSubtraction, glm::vec3);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec3);

BENCHMARK_TEMPLATE(VecSubtraction, glm::vec4);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec4);

BENCHMARK_TEMPLATE(VecMultiplication, XMVECTOR);
BENCHMARK_TEMPLATE(VecMultiplication, glm::vec2);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec2);

BENCHMARK_TEMPLATE(VecMultiplication, glm::vec3);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec3);

BENCHMARK_TEMPLATE(VecMultiplication, glm::vec4);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec4);

BENCHMARK_TEMPLATE(VecDivision, XMVECTOR);
BENCHMARK_TEMPLATE(VecDivision, glm::vec2);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec2);

BENCHMARK_TEMPLATE(VecDivision, glm::vec3);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec3);

BENCHMARK_TEMPLATE(VecDivision, glm::vec4);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec4);

}  // namespace
