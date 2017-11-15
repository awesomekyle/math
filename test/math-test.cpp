#include "akmath.h"
#include "catch.hpp"

TEST_CASE("vec2 creation")
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
}
