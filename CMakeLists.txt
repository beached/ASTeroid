cmake_minimum_required( VERSION 2.8.12 )
include( ExternalProject )
project( asteroid_prj )

include( ExternalProject )

set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )
find_package( Boost 1.59.0 REQUIRED COMPONENTS system filesystem unit_test_framework date_time )

IF( ${CMAKE_CXX_COMPILER_ID} STREQUAL 'MSVC' )
	add_compile_options( -D_WIN32_WINNT=0x0601 ) 
ELSE( )
	find_package( Threads REQUIRED )
	if( THREADS_HAVE_PTHREAD_ARG )
		set( COMPILER_SPECIFIC_LIBS, "-lpthread" )
	endif()

	if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang" )
		add_compile_options(-std=c++14 -Weverything -Wno-c++98-compat -Wfatal-errors -Wno-covered-switch-default -Wno-padded -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-missing-noreturn -Wno-missing-prototypes -Wno-disabled-macro-expansion)		
	ELSEIF( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
		add_compile_options(-std=c++14 -Wall -Wno-deprecated-declarations)
	ENDIF()
ENDIF()

ExternalProject_Add( 
	header_libraries_prj
	GIT_REPOSITORY "https://github.com/beached/header_libraries.git"
	SOURCE_DIR "${CMAKE_BINARY_DIR}/3rdparty/header_libraries"
	GIT_TAG "master"
	INSTALL_DIR "${CMAKE_BINARY_DIR}/install"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
 )

include_directories( SYSTEM "${CMAKE_BINARY_DIR}/install/include" )
include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )

set( HEADER_FOLDER "include" )
include_directories( ${HEADER_FOLDER} )

set( HEADER_FILES
	${HEADER_FOLDER}/asteroid.h
)

set( SOURCE_FILES
	asteroid.cpp
)

add_library( asteroid ${SOURCE_FILES} ${HEADER_FILES} )
add_dependencies( asteroid header_libraries_prj )

target_link_libraries( asteroid ${CMAKE_DL_LIBS} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${COMPILER_SPECIFIC_LIBS} )


install( TARGETS asteroid DESTINATION lib )
install( DIRECTORY ${HEADER_FOLDER}/ DESTINATION include/daw/asteroid )

