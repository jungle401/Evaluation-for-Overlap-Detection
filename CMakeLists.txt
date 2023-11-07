cmake_minimum_required (VERSION 3.16)

# project name
project(app)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/)

add_definitions( -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" )
message(STATUS "PROJECT_SOURCE_DIR" ${PROJECT_SOURCE_DIR})

# OpenMP
# Find OpenMP package
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Boost
FIND_PACKAGE( Boost 1.73.0 COMPONENTS program_options REQUIRED )

# fmt
FIND_PACKAGE(fmt REQUIRED)
IF (Boost_FOUND)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
	message(STATUS ${BOOST_ROOT})
	message(STATUS ${Boost_LIBRARY_DIRS})
	message(STATUS ${BOOST_INCLUDEDIR})
ENDIF()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-sign-compare")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
  src/main.cpp
  src/options.cpp)

add_executable(app ${SOURCES})

TARGET_LINK_LIBRARIES(app Boost::program_options)
TARGET_LINK_LIBRARIES(app fmt::fmt)
target_link_libraries(app OpenMP::OpenMP_CXX)


target_compile_options(app PRIVATE -g)
