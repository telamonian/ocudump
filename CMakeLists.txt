cmake_minimum_REQUIRED(VERSION 3.0.2)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(OCULUS_SDK_ROOT_DIR /usr/local/OculusSDK CACHE PATH "Path where to find the Oculus SDK")

################
project(ocudump)
################

IF(DEFINED CUSTOM_C_FLAGS)
    SET(CMAKE_C_FLAGS ${CUSTOM_C_FLAGS})
    MESSAGE(STATUS "Using custom C flags: ${CMAKE_C_FLAGS}")
ELSE(DEFINED CUSTOM_C_FLAGS)
    SET(CMAKE_C_FLAGS "-g -m64 -fPIC -fmessage-length=0")    #-Wall
ENDIF(DEFINED CUSTOM_C_FLAGS)

IF(DEFINED CUSTOM_CXX_FLAGS)
    SET(CMAKE_CXX_FLAGS ${CUSTOM_CXX_FLAGS})
    MESSAGE(STATUS "Using custom C++ flags: ${CMAKE_CXX_FLAGS}")
ELSE(DEFINED CUSTOM_CXX_FLAGS)
    SET(CMAKE_CXX_FLAGS "-g -m64 -fPIC -fmessage-length=0")    #-Wall
ENDIF(DEFINED CUSTOM_CXX_FLAGS)

# package finding stuff
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules)

find_package(OculusSDK REQUIRED)
if(${OCULUS_SDK_VERSION} VERSION_LESS 0.6.0.0)
    add_definitions(-DOVRSDK5)
else(${OCULUS_SDK_VERSION} VERSION_LESS 0.6.0.0)
    add_definitions(-DOVRSDK6)
endif(${OCULUS_SDK_VERSION} VERSION_LESS 0.6.0.0)
find_package(Eigen3)
if(EIGEN3_FOUND)
    add_definitions(-DUSE_EIGEN)
endif(EIGEN3_FOUND)

include_directories(src/c/
                    test/c/
                    ${CMAKE_CURRENT_BINARY_DIR}/src/c/
                    ${CMAKE_CURRENT_BINARY_DIR}/test/c/
                    ${OCULUS_SDK_INCLUDE_DIRS})

# add subdirectories
add_subdirectory(src/c)
add_subdirectory(test/c)

################
#TARGET: dumpTest
################
set(dumpTest_src test/c/dumpTest.cpp)

add_executable(dumpTest ${dumpTest_src})
target_link_libraries(dumpTest ocudump_lib)

# The following code is need to ensue that all objects from the custom static libraries are
# linked in to the executable, even if they are not referenced from the main program.
# Without this, static initialization of the ClassFactory does not work.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(dumpTest -Wl,--whole-archive)
    target_link_libraries(dumpTest ocudump_lib)
    target_link_libraries(dumpTest -Wl,--no-whole-archive)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(dumpTest -Wl,-force_load)
    target_link_libraries(dumpTest ocudump_lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

find_package(Cython)
if(CYTHON_FOUND)
    add_custom_target(ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/ReplicatePythonSourceTree.cmake
        ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    include(UseCython)  ###cython
    
    add_subdirectory(src/cython)
    add_subdirectory(test/python)
else(CYTHON_FOUND)
    message("Cython not found, python bindings won't be built")
endif(CYTHON_FOUND)