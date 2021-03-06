#include "akmath.h"
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>
#include <DirectXMath.h>
#pragma warning(disable : 4577)  // 'noexcept' used
#include <Eigen/Core>
#include <Eigen/Dense>

namespace {

using namespace DirectX;
using namespace ak;

enum {
    kLoopCount = 128,
};

constexpr float kMinTime = 0.0125f;

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

// Eigen
void FillVec(Eigen::Vector2f& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(Eigen::Vector3f& v)
{
    v = {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f)};
}
void FillVec(Eigen::Vector4f& v)
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
#if 0
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

#endif

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

void FillMatrix(DirectX::XMMATRIX& m)
{
    m = XMMatrixSet(RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
                    RandFloat(-50.0f, 50.0f));
}
void FillMatrix(ak::Mat4& m)
{
    m = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
    };
}
void FillMatrix(glm::mat4& m)
{
    m = {
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
        {RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
         RandFloat(-50.0f, 50.0f)},
    };
}
void FillMatrix(Eigen::Matrix4f& m)
{
    m << RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f), RandFloat(-50.0f, 50.0f),
        RandFloat(-50.0f, 50.0f);
}

template<typename Matrix>
void Mat4Multiplication(benchmark::State& state)
{
    Matrix m1, m2;
    FillMatrix(m1);
    FillMatrix(m2);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize((Matrix)(m1 * m2));
        }
    }
}
BENCHMARK_TEMPLATE(Mat4Multiplication, XMMATRIX);
BENCHMARK_TEMPLATE(Mat4Multiplication, glm::mat4);
BENCHMARK_TEMPLATE(Mat4Multiplication, Eigen::Matrix4f);
BENCHMARK_TEMPLATE(Mat4Multiplication, ak::Mat4);

template<typename Matrix, typename Vector>
void Mat4VecMultiplication(benchmark::State& state)
{
    Matrix m1, m2;
    Vector v1, v2;
    FillMatrix(m1);
    FillMatrix(m2);
    FillVec(v1);
    FillVec(v2);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize((Vector)(m1 * v1));
        }
    }
}

template<>
void Mat4VecMultiplication<XMMATRIX, XMVECTOR>(benchmark::State& state)
{
    XMMATRIX m1, m2;
    XMVECTOR v1, v2;
    FillMatrix(m1);
    FillMatrix(m2);
    FillVec(v1);
    FillVec(v2);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount; ++ii) {
            benchmark::DoNotOptimize(XMVector4Transform(v1, m1));
        }
    }
}
BENCHMARK_TEMPLATE(Mat4VecMultiplication, XMMATRIX, XMVECTOR);
BENCHMARK_TEMPLATE(Mat4VecMultiplication, glm::mat4, glm::vec4);
BENCHMARK_TEMPLATE(Mat4VecMultiplication, Eigen::Matrix4f, Eigen::Vector4f);
BENCHMARK_TEMPLATE(Mat4VecMultiplication, ak::Mat4, ak::Vec4);

void DxMat4Inverse(benchmark::State& state)
{
    DirectX::XMMATRIX m;
    FillMatrix(m);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(XMMatrixInverse(nullptr, m));
        }
    }
}
BENCHMARK(DxMat4Inverse);

void GlmMat4Inverse(benchmark::State& state)
{
    glm::mat4 m;
    FillMatrix(m);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(glm::inverse(m));
        }
    }
}
BENCHMARK(GlmMat4Inverse);

void EigenMat4Inverse(benchmark::State& state)
{
    Eigen::Matrix4f m;
    FillMatrix(m);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize((Eigen::Matrix4f)m.inverse());
        }
    }
}
BENCHMARK(EigenMat4Inverse);

void Mat4Inverse(benchmark::State& state)
{
    ak::Mat4 m;
    FillMatrix(m);
    for (auto _ : state) {
        for (int ii = 0; ii < kLoopCount / 4; ++ii) {
            benchmark::DoNotOptimize(ak::Inverse(m));
        }
    }
}
BENCHMARK(Mat4Inverse);

}  // namespace
