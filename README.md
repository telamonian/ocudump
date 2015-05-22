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
- The python module will now be at {your_build_directory}/src/cython/ocudump.so

# how to test
- To test the c++ library, after you run `make` in your build directory you can then run
    - `./dumpTest`
- To test the python module, after you run `make ocudump_cython` in your build directory you can then run
    - `python dumpTest.py`

# how to use (Python bindings)
- In order to use the Python bindings, copy the module at {your_build_directory}/src/cython/ocudump.so into the same directory as your Python scripts (or for an interactive session, just run `python` in the same directory as ocudump.so)
- Import the Ocudump class from the ocudump module:
    - `from ocudump import Ocudump`
- Create an Ocudump instance (this will also initialize your Oculus Rift and it's tracking camera, so be sure to have them both plugged in at this point):
    - `o = Ocudump()`
- Update the pose information contained in your Ocudump instance:
    - `o.getPose()`
- If your tracking camera was tracking position at the time when you got the last pose, Ocudump member variable `positionTracked` will be set to true. Otherwise, it will be set to False:
    - `print(o.positionTracked)`
- After you run `getPose()`, the `pose` Ocudump member variable will contain a list with six floating point numbers. The first three numbers are the rotation angles of the Oculus Rift pose, and the last 3 are the xyz position:
    - `o.pose` -> `[yaw, pitch, roll, x, y, z]`
    - In the case where the tracking camera is not currently tracking your Rift, the last three entries, where xyz normally go, will instead just contain `nan` values.
