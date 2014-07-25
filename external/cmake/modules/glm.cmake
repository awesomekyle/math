set(GLM_DIR "external/glm"
	CACHE PATH "The path to the GLM math library")

# set_property(TARGET gmock PROPERTY FOLDER "GTest")

include_directories(SYSTEM
	${GMOCK_DIR}
	${GMOCK_DIR}/gtc
	${GMOCK_DIR}/gtc
	)
