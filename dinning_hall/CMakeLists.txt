cmake_minimum_required (VERSION 3.9.4)

project (dinning_hall CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DINNING_HALL_DIR ${PROJECT_SOURCE_DIR})

set(DINNING_HALL_SRC
	${DINNING_HALL_DIR}/src/dinning_hall.cpp	
	)

include_directories(
	${DINNING_HALL_DIR}/inc
	${SERVER}/inc
	${CLIENT}/inc
	${MESSAGE}/inc
	${MESSAGE}/inc
	${HELPERS}
	)

add_library( ${PROJECT_NAME}
	${DINNING_HALL_SRC}
	)

target_link_libraries(${PROJECT_NAME} server client message)
