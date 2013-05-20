cmake_minimum_required(VERSION 2.6)

project(stratumLib)

set(ROOT_PATH   ${PROJECT_SOURCE_DIR}/../../)
set(SRC_PATH	${ROOT_PATH}/source)
set(OUT_PATH    ${ROOT_PATH}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x") 

# Stratum library
set(LIB_PATH	${PROJECT_SOURCE_DIR}/../../src)

set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/../../include)
include_directories(${INCLUDE_PATH})

set(LIB_SRC 	${LIB_PATH}/graphic_impl.cpp ${LIB_PATH}/core_impl.cpp
                
		${LIB_PATH}/log.cpp
		${LIB_PATH}/utility.cpp
		${LIB_PATH}/platform/linux.cpp)

# required libs
set(EXTRA_LIBS ${EXTRA_LIBS} libEGL.so libGLESv2.so)

find_package(Boost 1.53.0 COMPONENTS log system thread program_options REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  set(EXTRA_LIBS ${EXTRA_LIBS} ${Boost_LIBRARIES})
  add_definitions(-DBOOST_ALL_DYN_LINK)
endif(Boost_FOUND)

find_package(X11 REQUIRED)
if (X11_FOUND)
  include_directories(${X11_INCLUDE_DIRS})
  set(EXTRA_LIBS ${EXTRA_LIBS} ${X11_LIBRARIES})
endif(X11_FOUND)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_PATH})

add_library(Stratum SHARED ${LIB_SRC})

