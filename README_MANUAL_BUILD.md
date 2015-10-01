# ocudump
A simple, fast C++ library for getting the complete pose information from an Oculus Rift, with Python bindings. Meant to be an easy starting place for Rift-based projects that don't require the rendering functionality of the OculusSDK. Used in the [OcuMol-Leap project](https://github.com/lqtza/OcuMOL_Leap), which adds VR support to PyMol. Tested on OSX and Windows, should work on Linux too.

# dependencies
- CMake
- Cython (for the Python bindings)
- OculusSDK (the official one)
- Oculus Runtime (make sure your runtime and SDK versions match)
- On Windows, you will also need
    - Python (doesn't come preinstalled like on OSX)
    - Visual Studio (for the compilers)

If are on OSX, I strongly recommend using Homebrew to install CMake and Python, and then using pip to install Cython

# Build
## how to build on OSX
- Get the official OculusSDK and put it in your `/usr/local` directory
- In the ocudump root, execute the following commands
    - `mkdir build`
    - `cd build`
    - `cmake ..`
    - `make`
- The c++ library will now be at `{your_build_directory}/src/c/libocudump_lib.a`
- The python module will now be at `{your_build_directory}/src/cython/ocudump.so`

## how to build on Windows
- Get the official OculusSDK and put it in your `C:\usr\local` directory
- In the ocudump root, execute the following commands
    - for 32-bit build:
        - `mkdir build`
        - `cd build`
        - `cmake -G "Visual Studio 12 2013" ..`
            - You'll probably need to change the above line if you have a different version of Visual Studio
        - `cmake --build . --config Release`
    - for 64-bit build:
        - `mkdir build`
        - `cd build`
        - `cmake -G "Visual Studio 12 2013 Win64" ..`
            - You'll probably need to change the above line if you have a different version of Visual Studio
        - `cmake --build . --config Release`
- The c++ library will now be at `{your_build_directory}\src\c\Release\ocudump_lib.lib`
- The python module will now be at `{your_build_directory}\src\cython\Release\ocudump.pyd`

# Install
## installing the python bindings
- Follow the Build instructions, then `cd` back to the ocudump root directory.
- Run `pip install -e .` 
  - The above command will get `pip` to install ocudump in development mode, meaning that it will create a kind of soft link between your python module directory and the ocudump directory.
  - Eventually ocudump will also be available directly through pypi.

# Test
## testing the c++ lib
- To test the c++ library, after you run `make` in your build directory you can then run
    - `./dumpTest`

## testing the python bindings
- To test the python module, after you run `make ocudump_cython` in your build directory you can then run
    - `python dumpTest.py`

# Instructions
## how to use the python bindings
- Follow the relevant Build and Install instructions
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
