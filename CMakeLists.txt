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

################
#TARGET: dumpTest
################
set(dumpTest_src src/c/dumpTest.cpp)

add_executable(dumpTest ${dumpTest_src})
target_link_libraries(dumpTest ocudump_lib)

# The following code is need to ensue that all objects from the custom static libraries are
# linked in to the executable, even if they are not referenced from the main program.
# Without this, static initialization of the ClassFactory does not work.
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(dumpTest -Wl,--whole-archive)
    target_link_libraries(dumpTest ocudump_lib)
    target_link_libraries(dumpTest -Wl,--no-whole-archive)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(dumpTest -Wl,-force_load)
    target_link_libraries(dumpTest ocudump_lib)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#target_link_libraries(dumpTest)