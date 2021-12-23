cmake_minimum_required (VERSION 3.9.4)

project (test_serv CXX)

set(TEST_SERV_DIR ${PROJECT_SOURCE_DIR})

set(TEST_SERV_SRC
	${TEST_SERV_DIR}/${PROJECT_NAME}.cpp
	)

include_directories(${SERVER}/inc)

add_executable( ${PROJECT_NAME}
	${TEST_SERV_SRC}
	)

target_link_libraries(${PROJECT_NAME} server)

