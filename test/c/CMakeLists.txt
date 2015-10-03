# c src directory

#################
#TARGET: sdkTest
#################

#get the source files
file(GLOB sdkTest_src sdkTest.cpp)
file(GLOB dumpTest_src dumpTest.cpp dumpTestDebug.cpp)

add_executable(sdkTest ${sdkTest_src})
target_link_libraries(sdkTest ${OCULUS_SDK_LIBRARIES})
set_target_properties(sdkTest PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE EXCLUDE_FROM_ALL TRUE)
