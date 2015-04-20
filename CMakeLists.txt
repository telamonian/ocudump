cmake_minimum_REQUIRED(VERSION 3.0.2)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
set(ENV{HDF5_ROOT} ${HDF5_ROOT})

SET(OCULUS_SDK_ROOT_DIR /usr/local/OculusSDK CACHE PATH "Path where to find the Oculus SDK")

################
project(ocudump)
################

# package finding stuff
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(OculusSDK REQUIRED)

include_directories(src/c/
                    ${CMAKE_CURRENT_BINARY_DIR}/src/c/
                    ${OCULUS_SDK_INCLUDE_DIRS})

# add subdirectories
add_subdirectory(src/c)             