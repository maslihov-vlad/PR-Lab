cmake_minimum_required (VERSION 3.9.4)

project (test_clt CXX)

set(TEST_CLT_DIR ${PROJECT_SOURCE_DIR})

set(TEST_CLT_SRC
	${TEST_CLT_DIR}/${PROJECT_NAME}.cpp
	)

include_directories(
	${CLIENT}/inc
	${MESSAGE}/inc
	${HELPERS}
	)

add_executable( ${PROJECT_NAME}
	${TEST_CLT_SRC}
	)

target_link_libraries(${PROJECT_NAME} client message)

