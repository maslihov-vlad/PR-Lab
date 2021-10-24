cmake_minimum_required (VERSION 3.9.4)

project (server CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SERVER_DIR ${PROJECT_SOURCE_DIR})

set(SERVER_SRC
	${SERVER_DIR}/src/server.cpp
	)

include_directories(
	${SERVER_DIR}/inc
	${MESSAGE}/inc
	${HELPERS}
	)

add_library(${PROJECT_NAME} 
	${SERVER_SRC}
	)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message ${Boost_LIBRARIES})
