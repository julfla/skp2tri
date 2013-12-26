# Add Boost program_options libraires to the project

project(skp2tri)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/module)
IF(NOT DEFINED EXECUTABLE_OUTPUT_PATH)
	SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
ENDIF(NOT DEFINED EXECUTABLE_OUTPUT_PATH)

IF(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
        SET(ERROR_MESSAGE "The project cannot be compiled for Linux, cross-compilation is required."\n)
	SET(ERROR_MESSAGE ${ERROR_MESSAGE} "Please look at the example toolchain file : "${TOOLCHAIN_FILE}\n)
	SET(ERROR_MESSAGE ${ERROR_MESSAGE} "If you want to use it clean the build folder and rerun cmake with the option : \n -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE})
	MESSAGE( FATAL_ERROR ${ERROR_MESSAGE})
ENDIF()

FIND_PACKAGE(Slapi REQUIRED)
IF( NOT SLAPI_FOUND )
    MESSAGE( FATAL_ERROR "Module Slapi required and not found.")
ENDIF()
INCLUDE_DIRECTORIES(${SLAPI_INCLUDE_DIR})

# Add the project skp2tri link to libraires
add_executable(skp2tri skp2tri.cxx )
	
target_link_libraries(skp2tri ${SLAPI_LIBRARIES})

add_custom_command(TARGET skp2tri POST_BUILD        # Adds a post-build event to skp-reader
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SLAPI_LIBRARY}" ${EXECUTABLE_OUTPUT_PATH}
)
