# c src directory

#################
#TARGET: ocudump_lib
#################
#get the source files
file(GLOB_RECURSE ocudump_c_src *.cpp *.cc *.h)
file(GLOB sdkTest_src sdkTest.cpp)
file(GLOB dumpTest_src dumpTest.cpp)
list(REMOVE_ITEM ocudump_c_src ${sdkTest_src} ${dumpTest_src})

add_library(ocudump_lib STATIC ${ocudump_c_src})
target_link_libraries(ocudump_lib ${OCULUS_SDK_LIBRARIES})

#################
#TARGET: sdkTest
#################
add_executable(sdkTest ${sdkTest_src})
target_link_libraries(sdkTest ${OCULUS_SDK_LIBRARIES})
set_target_properties(sdkTest PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE EXCLUDE_FROM_ALL TRUE)
