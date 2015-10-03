# c src directory

#################
#TARGET: ocudump_lib
#################
#get the source files
file(GLOB_RECURSE ocudump_c_src *.cpp *.cc *.h)

add_library(ocudump_lib STATIC ${ocudump_c_src})
target_link_libraries(ocudump_lib ${OCULUS_SDK_LIBRARIES})