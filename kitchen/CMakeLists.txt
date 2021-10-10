cmake_minimum_required (VERSION 3.9.4)

project (kitchen CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(KITCHEN_DIR ${PROJECT_SOURCE_DIR})

set(KITCHEN_SRC
	${KITCHEN_DIR}/src/kitchen.cpp
	)

include_directories(
	${KITCHEN_DIR}/inc
	${SERVER}/inc
	${CLIENT}/inc
	${MESSAGE}/inc
	${HELPERS}
	)

add_library( ${PROJECT_NAME}
	${KITCHEN_SRC}
	)

target_link_libraries(${PROJECT_NAME} server client message)
