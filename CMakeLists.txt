cmake_minimum_REQUIRED(VERSION 3.0.2)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(OCULUS_SDK_ROOT_DIR /usr/local/OculusSDK CACHE PATH "Path where to find the Oculus SDK")

################
project(ocudump)
################

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
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(dumpTest -Wl,--whole-archive)
    target_link_libraries(dumpTest ocudump_lib)
    target_link_libraries(dumpTest -Wl,--no-whole-archive)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(dumpTest -Wl,-force_load)
    target_link_libraries(dumpTest ocudump_lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

################
#TARGET: dumpTestDebug
################
set(dumpTestDebug_src src/c/dumpTestDebug.cpp)

add_executable(dumpTestDebug ${dumpTestDebug_src})
target_link_libraries(dumpTestDebug ocudump_lib)

# The following code is need to ensue that all objects from the custom static libraries are
# linked in to the executable, even if they are not referenced from the main program.
# Without this, static initialization of the ClassFactory does not work.
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(dumpTestDebug -Wl,--whole-archive)
    target_link_libraries(dumpTestDebug ocudump_lib)
    target_link_libraries(dumpTestDebug -Wl,--no-whole-archive)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(dumpTestDebug -Wl,-force_load)
    target_link_libraries(dumpTestDebug ocudump_lib)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

################
#TARGET: cython
################
#set(CYTHON_OTHER_LIBS ${CMAKE_THREAD_LIBS_INIT}
#                      ${libsbml_LIBRARIES}
#                      ${PROTOBUF_LIBRARIES}
#                      ${HDF5_LIBRARIES}
#                      ${HDF5_HL_LIBRARIES}
#                      ${MPI_C_LIBRARIES}
#                      ${PYTHON_LIBRARY_DIRS})

find_package(Cython)
if(CYTHON_FOUND)
    add_custom_target(ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/ReplicatePythonSourceTree.cmake
        ${CMAKE_CURRENT_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    include(UseCython)  ###cython
    
    add_subdirectory(src/cython)
else(CYTHON_FOUND)
    message("Cython not found, python bindings won't be built")
endif(CYTHON_FOUND)