from distutils.spawn import find_executable
from distutils.sysconfig import get_python_lib
import glob
import os,sys
from setuptools import setup

from utils import option_value

OPTION_CMAKE = option_value("cmake")
if OPTION_CMAKE is None:
    OPTION_CMAKE = find_executable("cmake")
if OPTION_CMAKE is None or not os.path.exists(OPTION_CMAKE):
    raise DistutilsSetupError(
        "Failed to find cmake."
        " Please specify the path to cmake with --cmake parameter.")

def build_extension(self, extension):
    # Build module
    cmake_cmd = [
        OPTION_CMAKE,
        "-G", self.make_generator,
    #     "-DQT_QMAKE_EXECUTABLE=%s" % self.qmake_path,
    #     "-DBUILD_TESTS=%s" % self.build_tests,
    #     "-DDISABLE_DOCSTRINGS=True",
    #     "-DCMAKE_BUILD_TYPE=%s" % self.build_type,
    #     "-DCMAKE_INSTALL_PREFIX=%s" % self.install_dir,
        module_src_dir
    ]
    
    if sys.platform == 'win32':
        cmake_cmd.append("-DCMAKE_BUILD_TYPE=%s" % 'Release')
        cmake_cmd.append("-DCMAKE_DEBUG_POSTFIX=_d")

setup(
    name = "ocudump",
    package_dir = {'': 'build/src/cython'},
    data_files = [(get_python_lib(), glob.glob('build/src/cython/*.so'))],
    author = 'Max Klein',
    description = 'lightweight library for dumping out tracking data from an Oculus Rift',
    license = 'UIOSL',
    zip_safe = False,
    )