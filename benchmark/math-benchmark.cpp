#include "akmath.h"
#include <benchmark/benchmark.h>

namespace {

static void Vec2Creation(benchmark::State& state)
{
    for (auto _ : state) {
        ak::Vec2 vec;
        (void)vec;
    }
}
BENCHMARK(Vec2Creation);

}  // namespace
