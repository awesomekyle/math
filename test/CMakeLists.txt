set(SOURCES 
	${PROJECT_SOURCE_DIR}/src/vec_math.h
	math_test.cpp
	math_test_c.c
	math_test_glm.cpp)

if(MSVC)
	set(SOURCES ${SOURCES} math_test_dx.cpp)
endif()

add_gmock_test(MathTest ${SOURCES})
