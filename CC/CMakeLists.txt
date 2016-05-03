cmake_minimum_required(VERSION 3.0)
if (POLICY CMP0042)
    cmake_policy (SET CMP0042 OLD)
endif()

project(MUONTOMO)

set(${PROJECT_NAME}_VERSION "1.0.0")
set(${PROJECT_NAME}_VERSION_MAJOR "1")
set(${PROJECT_NAME}_VERSION_MINOR "0")
set(${PROJECT_NAME}_VERSION_PATCH "0")
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "-w -fPIC -O0")
add_definitions(-std=c++11)

find_package(ROOT REQUIRED)
add_definitions(${ROOT_DEFINITIONS})
include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${MUONTOMO_SOURCE_DIR}/include)
include_directories(${MUONTOMO_SOURCE_DIR}/src)

set(LIBS ${ROOT_LIBRARY_DIR}//libCore.so ${ROOT_LIBRARY_DIR}/libRIO.so ${ROOT_LIBRARY_DIR}/libGeom.so ${ROOT_LIBRARY_DIR}/libGraf.so ${ROOT_LIBRARY_DIR}/libGpad.so ${ROOT_LIBRARY_DIR}/libHist.so ${ROOT_LIBRARY_DIR}/libEG.so ${ROOT_LIBRARY_DIR}/libPhysics.so ${ROOT_LIBRARY_DIR}/libMathMore.so)

set (exec_INCS  ${MUONTOMO_SOURCE_DIR}/include/base.h ${MUONTOMO_SOURCE_DIR}/include/hodoscope.h ${MUONTOMO_SOURCE_DIR}/include/muon.h ${MUONTOMO_SOURCE_DIR}/include/sensor.h)

set (exec_SRCS ${MUONTOMO_SOURCE_DIR}/src/muonTomography.cpp)

add_executable(muontomo.e ${exec_INCS}  ${exec_SRCS})
target_link_libraries(muontomo.e ${LIBS})

