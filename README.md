# ocudump
A simple, fast C++ library for getting the complete pose information from an Oculus Rift, with Python bindings. Meant to be an easy starting place for Rift-based projects that don't require the rendering functionality of the OculusSDK. Used in the OcuMol-Leap project, which adds VR support to PyMol. Tested on OSX, should work on Linux and Windows too.

# dependencies
- CMake
- Cython (for the Python bindings)
- OculusSDK (the official one)

If are on OSX, I strongly recommend using Homebrew to install CMake and Python, and then using pip to install Cython

# how to build
- Get the official OculusSDK and put it in your /usr/local directory
- In the ocudump root, execute the following commands
    - `mkdir build`
    - `cd build`
    - `cmake ..`
    - `make`
- The c++ library will now be at {your_build_directory}/src/c/libocudump_lib.a
- To make the Python bindings, also do
    - `make ocudump_cython`
- The python module will now be at {your_build_directory}/src/cython/ocudump_cython.so

# how to test
- To test the c++ library, after you run `make` in your build directory you can then run
    - `./dumpTest`
- To test the python module, after you run `make ocudump_cython` in your build directory you can then run
    - `python dumpTest.py`

# how to use
