cmake_minimum_required(VERSION 2.6)

project(stratumSamples)

set(ROOT_PATH   ${PROJECT_SOURCE_DIR}/../../..)
set(SRC_PATH	 ${PROJECT_SOURCE_DIR}/../..)
set(INCLUDE_PATH ${ROOT_PATH}/include)
set(LIB_PATH ${ROOT_PATH}/lib)

set(EXE_SRC 	${SRC_PATH}/main.cpp)

set(EXTRA_LIBS Stratum libEGL.so libGLESv2.so)
include_directories(${INCLUDE_PATH})
link_directories(${LIB_PATH})

set(EXECUTABLE_NAME test)

add_executable(${EXECUTABLE_NAME} ${EXE_SRC})

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

target_link_libraries (${EXECUTABLE_NAME} ${EXTRA_LIBS})
