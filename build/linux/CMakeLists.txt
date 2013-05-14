cmake_minimum_required(VERSION 2.6)

project(stratum)

set(SRC_PATH	${PROJECT_SOURCE_DIR}/../../source)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11") 

# Stratum library
set(LIB_PATH	${PROJECT_SOURCE_DIR}/../../source/lib)


set(LIB_SRC 	${LIB_PATH}/graphic.cpp
		${LIB_PATH}/log.cpp
		${LIB_PATH}/utility.cpp
		${LIB_PATH}/platform/linux.cpp)

add_library(Stratum SHARED ${LIB_SRC})
set (EXTRA_LIBS Stratum)

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

# exe
set(EXECUTABLE_NAME test)
set(EXE_SRC ${SRC_PATH}/example/main.cpp)
include_directories ("${LIB_PATH}")
add_executable(${EXECUTABLE_NAME} ${EXE_SRC})

target_link_libraries (${EXECUTABLE_NAME} ${EXTRA_LIBS})

