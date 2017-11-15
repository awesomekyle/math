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

constexpr float kMinTime = 0.25f;

float RandFloat(float const min, float const max)
{
    float f = rand() / static_cast<float>(RAND_MAX);
    f *= (max - min);
    return f + min;
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

BENCHMARK_TEMPLATE(VecAddition, XMVECTOR)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecAddition, glm::vec2)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec2)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecAddition, glm::vec3)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec3)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecAddition, glm::vec4)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecAddition, ak::Vec4)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecSubtraction, XMVECTOR)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecSubtraction, glm::vec2)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec2)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecSubtraction, glm::vec3)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec3)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecSubtraction, glm::vec4)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecSubtraction, ak::Vec4)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecMultiplication, XMVECTOR)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecMultiplication, glm::vec2)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec2)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecMultiplication, glm::vec3)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec3)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecMultiplication, glm::vec4)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecMultiplication, ak::Vec4)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecDivision, XMVECTOR)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecDivision, glm::vec2)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec2)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecDivision, glm::vec3)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec3)->MinTime(kMinTime);

BENCHMARK_TEMPLATE(VecDivision, glm::vec4)->MinTime(kMinTime);
BENCHMARK_TEMPLATE(VecDivision, ak::Vec4)->MinTime(kMinTime);

void DxMat3Inverse(benchmark::State& state)
{
    DirectX::XMMATRIX const m =
        XMMatrixSet(RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f));
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(XMMatrixInverse(nullptr, m));
        }
    }
}
BENCHMARK(DxMat3Inverse);

void GlmMat3Inverse(benchmark::State& state)
{
    glm::mat3 const m = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
    };
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(glm::inverse(m));
        }
    }
}
BENCHMARK(GlmMat3Inverse);

void Mat3Inverse(benchmark::State& state)
{
    ak::Mat3 const m = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)},
    };
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(ak::Inverse(m));
        }
    }
}
BENCHMARK(Mat3Inverse);

}  // namespace
