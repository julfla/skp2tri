# Add Boost program_options libraires to the project

project(skp2tri)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/module)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

IF(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	SET(TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/Toolchain-windows-mingw32.cmake)
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

find_package(Boost 1.49.0 COMPONENTS program_options)

# Add the project skp2tri link to libraires
add_executable(skp2tri skp2tri.cxx )

IF (NOT Boost_FOUND)
	MESSAGE( "Boost cannot be found, it will be downloaded and compiled automatically.")
	
	# External_Project Boost if compilation is needed
	INCLUDE( ExternalProject )
	SET( Boost_bjam_ARGS
		toolset=gcc-mingw
		target-os=windows
		#threadapi=win32
		#threading=multi
		#variant=release
		--user-config=./user-config.jam
		--layout=tagged 
	)

	ExternalProject_Add(boost_program_options
		URL http://sourceforge.net/projects/boost/files/boost/1.54.0/boost_1_54_0.tar.bz2/download
		PATCH_COMMAND echo using gcc : mingw : i586-mingw32msvc-g++ : 4.2 \\073 >> user-config.jam
		BUILD_IN_SOURCE 1
		CONFIGURE_COMMAND ./bootstrap.sh --with-libraries=program_options
		BUILD_COMMAND ./bjam ${Boost_bjam_ARGS}
		INSTALL_COMMAND ""
		#INSTALL_COMMAND ./bjam install ${Boost_bjam_ARGS}
	)
	add_dependencies(skp2tri boost_program_options)
	
	ExternalProject_Get_Property(boost_program_options SOURCE_DIR)
	SET( Boost_LIBRARIES ${SOURCE_DIR}/stage/lib/libboost_program_options-mt.a)
	SET( Boost_INCLUDE_DIR ${SOURCE_DIR})

ENDIF()

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

target_link_libraries(skp2tri ${SLAPI_LIBRARIES} ${Boost_LIBRARIES})

add_custom_command(TARGET skp2tri POST_BUILD        # Adds a post-build event to skp-reader
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SLAPI_LIBRARY}" ${EXECUTABLE_OUTPUT_PATH}
)
