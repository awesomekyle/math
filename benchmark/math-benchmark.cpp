#include "akmath.h"
#include <benchmark/benchmark.h>
#include <glm/glm.hpp>

namespace {

static void Vec2Creation(benchmark::State& state)
{
    for (auto _ : state) {
        ak::Vec2 vec;
        (void)vec;
    }
}
BENCHMARK(Vec2Creation);

static void GLMVec4Multiplication(benchmark::State& state)
{
    glm::vec4 a{1, 2, 3, 4};
    glm::vec4 b{50, 60, 70, 80};
    for (auto _ : state) {
        for (int ii = 0; ii < 100; ++ii) {
            benchmark::DoNotOptimize(a * b);
        }
    }
}
BENCHMARK(GLMVec4Multiplication);

}  // namespace
