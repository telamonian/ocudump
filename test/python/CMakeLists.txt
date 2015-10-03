# Copy testing files over to build dir
file(GLOB dumptest_py dumpTest.py dumpTestDebug.py)
file(GLOB init_py __init__.py)

file(COPY ${dumptest_py} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${init_py} DESTINATION ${CMAKE_BINARY_DIR})
