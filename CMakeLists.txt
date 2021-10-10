cmake_minimum_required (VERSION 3.0)

project(lab_ CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_FLAGS "-O3 -fpermissive -Wextra")


set (LAB_DIR ${PROJECT_SOURCE_DIR})

set (CLIENT_SERVICE ${LAB_DIR}/client_service)
set (DINING_HALL ${LAB_DIR}/dinning_hall)
set (KITCHEN ${LAB_DIR}/kitchen)

set (HELPERS ${LAB_DIR}/helpers)

set (MESSAGE ${LAB_DIR}/message)
set (SERVER ${LAB_DIR}/server)
set (CLIENT ${LAB_DIR}/client)

find_package(Boost REQUIRED COMPONENTS system thread)

add_subdirectory(${MESSAGE})
add_subdirectory(${CLIENT})
add_subdirectory(${SERVER})

add_subdirectory(${DINING_HALL})
add_subdirectory(${KITCHEN})


if (ENABLE_TESTING) 
	# add_subdirectory(tests/base_test)
	add_subdirectory(tests/test_serv)
	add_subdirectory(tests/test_clt)
endif()
