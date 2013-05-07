cmake_minimum_required(VERSION 2.6)

project(stratum)

set(EXECUTABLE_NAME test)
set(SRC_PATH	${PROJECT_SOURCE_DIR}/../../source)
set(EXTRA_LIBS	libEGL.so libGLESv2.so)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 

set(SOURCES 	${SRC_PATH}/graphic.cpp
		${SRC_PATH}/main.cpp
		${SRC_PATH}/log.cpp
        ${SRC_PATH}/utility.cpp
		${SRC_PATH}/platform/linux.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

find_package(Boost 1.53.0 COMPONENTS log system thread REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  set(EXTRA_LIBS	${EXTRA_LIBS} ${Boost_LIBRARIES})
  add_definitions(-DBOOST_ALL_DYN_LINK)
#  foreach (toto ${Boost_LIBRARIES})
#	message(STATUS "${toto}")
#  endforeach()
endif(Boost_FOUND)

find_package(X11 REQUIRED)
if (X11_FOUND)
  include_directories(${X11_INCLUDE_DIRS})
  set(EXTRA_LIBS	${EXTRA_LIBS} ${X11_LIBRARIES})
endif(X11_FOUND)

target_link_libraries (${EXECUTABLE_NAME} ${EXTRA_LIBS})
  
