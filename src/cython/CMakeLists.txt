## Generate a single pair of .pyx and .pxd files from cython source tree
set(pyx_fpath ${CMAKE_CURRENT_BINARY_DIR}/ocudump.pyx)
set(pyx_tmp_fpath ${CMAKE_CURRENT_BINARY_DIR}/ocudump.pyx.tmp)
set(pxd_fpath ${CMAKE_CURRENT_BINARY_DIR}/ocudump.pxd)
set(pxd_tmp_fpath ${CMAKE_CURRENT_BINARY_DIR}/ocudump.pxd.tmp)

# Cmake "cat" function definition
function(cat IN_FILE OUT_FILE)
    file(READ ${IN_FILE} CONTENTS)
    file(APPEND ${OUT_FILE} "${CONTENTS}")
    file(APPEND ${OUT_FILE} "\n")
endfunction()

# Prepare temporary .pyx and .pxd files to "cat" to:
#file(REMOVE ocudump.pyx.tmp "")
#file(REMOVE ocudump.pxd.tmp "")
file(WRITE ${pyx_tmp_fpath} "")
file(WRITE ${pxd_tmp_fpath} "")

# Get two lists of all the .pyx and .pxd files by recursively globbing down the cython source tree
file(GLOB_RECURSE ocudump_pyxs *.pyx)
file(GLOB_RECURSE ocudump_pxds *.pxd)

file(GLOB to_remove_ocudump_pyx ocudump.pyx)
if(to_remove_ocudump_pyx)
    list(REMOVE_ITEM ocudump_pyxs ${to_remove_ocudump_pyx})
endif(to_remove_ocudump_pyx)

file(GLOB to_remove_ocudump_pxd ocudump.pxd)
if(to_remove_ocudump_pxd)
    list(REMOVE_ITEM ocudump_pxds ${to_remove_ocudump_pxd})
endif(to_remove_ocudump_pxd)

# Call the "cat" function for each of the cython source files
foreach(ocudump_pyx ${ocudump_pyxs})
    cat(${ocudump_pyx} ${pyx_tmp_fpath})
endforeach(ocudump_pyx ${ocudump_pyxs})

foreach(ocudump_pxd ${ocudump_pxds})
    cat(${ocudump_pxd} ${pxd_tmp_fpath})
endforeach(ocudump_pxd ${ocudump_pxds})

message(${CMAKE_CURRENT_BINARY_DIR})

# Copy the temporary .pyx and .pxd files to the final location
configure_file(${pyx_tmp_fpath} ${pyx_fpath} COPYONLY)
configure_file(${pxd_tmp_fpath} ${pxd_fpath} COPYONLY)

# Specify that the .pyx and .pxd files are generated
set_source_files_properties(${pyx_fpath}
                            ${pxd_fpath}
                            PROPERTIES GENERATED TRUE)

# Specify that the .pyx file is a C++ file.
set_source_files_properties(
    ${pyx_fpath}
    PROPERTIES CYTHON_IS_CXX TRUE)

## Build the actual cython .so file
set(ocudump_libs ocudump_lib)

# Multi-file cython modules do not appear to be working at the moment.
cython_add_module(ocudump ${pyx_fpath})
target_link_libraries(ocudump ${ocudump_libs})

# Copy testing files over to build dir
file(GLOB dumptest_py dumpTest.py dumpTestDebug.py)
file(GLOB init_py __init__.py)

file(COPY ${dumptest_py} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR}/src)
file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR}/src/cython)

#message(${CMAKE_BINARY_DIR}/src/cython/Release)
#IF(IS_DIRECTORY ${CMAKE_BINARY_DIR}/src/cython/Release)
    file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR}/src/cython/Release)
#ELSEIF(IS_DIRECTORY ${CMAKE_BINARY_DIR}/src/cython/Debug)
    file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR}/src/cython/Debug)
#ENDIF(IS_DIRECTORY ${CMAKE_BINARY_DIR}/src/cython/Release)

# If the pyx file is a C++ file, we should specify that here.
#set_source_files_properties(
#    test/Hdf5File.pyx
#    test/ReactionModel.pyx
#    PROPERTIES CYTHON_IS_CXX TRUE)
#
# Multi-file cython modules do not appear to be working at the moment.
#cython_add_module(ReactionModel test/ReactionModel.pyx)
#cython_add_module(Hdf5File test/Hdf5File.pyx)
#
#add_dependencies(Hdf5File ReactionModel)
#
#SET(LM_C_LIB lm_c_lib)
#IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    target_link_libraries(ReactionModel -Wl,--whole-archive)
#    target_link_libraries(ReactionModel ${LM_C_LIB})
#    target_link_libraries(ReactionModel -Wl,--no-whole-archive)
#ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    target_link_libraries(ReactionModel -Wl,-force_load)
#    target_link_libraries(ReactionModel ${LM_C_LIB})
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    target_link_libraries(Hdf5File -Wl,--whole-archive)
#    target_link_libraries(Hdf5File ${LM_C_LIB})
#    target_link_libraries(Hdf5File -Wl,--no-whole-archive)
#ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    target_link_libraries(Hdf5File -Wl,-force_load)
#    target_link_libraries(Hdf5File ${LM_C_LIB})
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#
#target_link_libraries(ReactionModel ${ocudump_libs})
#target_link_libraries(Hdf5File ${ocudump_libs})
#
#cython_add_module(ocudump test/ReactionModel.pyx)
#target_link_libraries(ocudump ${ocudump_libs})

#cython_add_modulehdf5 hdf5.pyx ${CMAKE_CURRENT_SOURCE_DIR}/src/c/lm/io/hdf5/SimulationFile.cpp)
