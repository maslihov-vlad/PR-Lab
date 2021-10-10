cmake_minimum_required (VERSION 3.9.4)

project (message CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MESSAGE_DIR ${PROJECT_SOURCE_DIR})

set(MESSAGE_SRC
	${MESSAGE_DIR}/src/message.cpp
	)

include_directories(
	${MESSAGE_DIR}/inc
	${HELPERS}
	)

add_library(${PROJECT_NAME} 
	${MESSAGE_SRC}
	)
