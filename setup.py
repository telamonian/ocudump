from setuptools import setup
from distutils.sysconfig import get_python_lib
import glob
import os
import sys

setup(
    name = "ocudump",
    package_dir = {'': 'src/cython'},
    data_files = [(get_python_lib(), glob.glob('src/cython/*.so'))],
    author = 'Max Klein',
    description = 'lightweight library for dumping out tracking data from an Oculus Rift',
    license = 'UIOSL',
    zip_safe = False,
    )
