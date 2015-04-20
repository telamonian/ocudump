# c src directory

#################
#TARGET: ocudump
#################
#get the source files
file(GLOB_RECURSE ocudump_c_src *.cpp *.cc *.h)
#file(GLOB to_remove_main_function lm/main/MainMPI.cpp)
#file(GLOB to_remove_neus lm/neus/*)
#list(REMOVE_ITEM lm_c_source ${to_remove_main_function} ${to_remove_neus})

add_executable(ocudump ${ocudump_c_src})
TARGET_LINK_LIBRARIES(ocudump ${OCULUS_SDK_LIBRARIES})
