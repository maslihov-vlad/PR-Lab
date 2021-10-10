cmake_minimum_required (VERSION 3.9.4)

project (client CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CLIENT_DIR ${PROJECT_SOURCE_DIR})

set(CLIENT_SRC
	${CLIENT_DIR}/src/client.cpp
	)

include_directories(
	${CLIENT_DIR}/inc
	${MESSAGE}/inc
	${HELPERS}
	)

add_library(${PROJECT_NAME} 
	${CLIENT_SRC}
	)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC message ${Boost_LIBRARIES})
